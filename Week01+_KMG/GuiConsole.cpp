#include "stdafx.h"
#include "GuiConsole.h"

int GuiConsole::Stricmp(const char* s1, const char* s2) { 
    int d; 
    while ( (d = toupper(*s2) - toupper(*s1)) == 0 && *s1 ) { 
        s1++; s2++; 
    } 
    return d;
}
int GuiConsole::Strnicmp(const char* s1, const char* s2, int n) { 
    int d = 0; 
    while ( n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1 ) { 
        s1++; s2++; n--; 
    } 
    return d; 
}

char* GuiConsole::Strdup(const char* s) { 
	IM_ASSERT(s); 
	size_t len = strlen(s) + 1; 
	void* buf = ImGui::MemAlloc(len); 
	IM_ASSERT(buf); 
	return (char*)memcpy(buf, (const void*)s, len); 
}

void GuiConsole::Strtrim(char* s) { 
	char* str_end = s + strlen(s); 
	while ( str_end > s && str_end[-1] == ' ' ) 
		str_end--; 
	*str_end = 0; 
}

void GuiConsole::Render() {
	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

	ImGui::Begin("Console");

	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar);
	for (const char* item: _items) {
		if ( _filter.PassFilter(item) )
			continue;
		ImGui::TextUnformatted(item);
	}
	ImGui::EndChild();
	ImGui::Separator();

    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion; // | ImGuiInputTextFlags_CallbackHistory;
    if ( ImGui::InputText("Input", _inputBuffer, IM_ARRAYSIZE(_inputBuffer), input_text_flags, [](ImGuiInputTextCallbackData* data) -> int {
        GuiConsole* console = (GuiConsole*)(data->UserData);
        return console->TextEditCallback(data);
    }, (void*)this) ) {
        OutputDebugString(L"console");
		char* s = _inputBuffer;
		Strtrim(s);
		/*if ( s[0] )
			ExecCommand(s);*/
		strcpy_s(s, 256, "");
	}
	ImGui::End();
}

void GuiConsole::AddLog(const char* fmt, ...) {
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);
	_items.push_back(Strdup(buf));
}

void GuiConsole::AddLog(const std::string str) {
	AddLog(str.c_str());
}

void GuiConsole::ClearLog() {
	for (auto& item: _items) {
		ImGui::MemFree(item);
	}
	_items.clear();
}

int GuiConsole::TextEditCallback(ImGuiInputTextCallbackData* data) {
    //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
    switch ( data->EventFlag ) {
    case ImGuiInputTextFlags_CallbackCompletion:
    {
        // Example of TEXT COMPLETION

        // Locate beginning of current word
        const char* word_end = data->Buf + data->CursorPos;
        const char* word_start = word_end;
        while ( word_start > data->Buf ) {
            const char c = word_start[-1];
            if ( c == ' ' || c == '\t' || c == ',' || c == ';' )
                break;
            word_start--;
        }

        // Build a list of candidates
        ImVector<const char*> candidates;
        for ( int i = 0; i < _commands.Size; i++ )
            if ( Strnicmp(_commands[i], word_start, (int)(word_end - word_start)) == 0 )
                candidates.push_back(_commands[i]);

        if ( candidates.Size == 0 ) {
            // No match
            AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
        } else if ( candidates.Size == 1 ) {
            // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
            data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
            data->InsertChars(data->CursorPos, candidates[0]);
            data->InsertChars(data->CursorPos, " ");
        } else {
            // Multiple matches. Complete as much as we can..
            // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
            int match_len = (int)(word_end - word_start);
            for ( ;;) {
                int c = 0;
                bool all_candidates_matches = true;
                for ( int i = 0; i < candidates.Size && all_candidates_matches; i++ )
                    if ( i == 0 )
                        c = toupper(candidates[i][match_len]);
                    else if ( c == 0 || c != toupper(candidates[i][match_len]) )
                        all_candidates_matches = false;
                if ( !all_candidates_matches )
                    break;
                match_len++;
            }

            if ( match_len > 0 ) {
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
            }

            // List matches
            AddLog("Possible matches:\n");
            for ( int i = 0; i < candidates.Size; i++ )
                AddLog("- %s\n", candidates[i]);
        }

        break;
    }
    //case ImGuiInputTextFlags_CallbackHistory:
    //{
    //    // Example of HISTORY
    //    const int prev_history_pos = HistoryPos;
    //    if ( data->EventKey == ImGuiKey_UpArrow ) {
    //        if ( HistoryPos == -1 )
    //            HistoryPos = History.Size - 1;
    //        else if ( HistoryPos > 0 )
    //            HistoryPos--;
    //    } else if ( data->EventKey == ImGuiKey_DownArrow ) {
    //        if ( HistoryPos != -1 )
    //            if ( ++HistoryPos >= History.Size )
    //                HistoryPos = -1;
    //    }

    //    // A better implementation would preserve the data on the current input line along with cursor position.
    //    if ( prev_history_pos != HistoryPos ) {
    //        const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
    //        data->DeleteChars(0, data->BufTextLen);
    //        data->InsertChars(0, history_str);
    //    }
    //}
    }
    return 0;
}