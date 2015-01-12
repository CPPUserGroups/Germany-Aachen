"""" Clang
let g:clang_use_library = 1
let g:clang_library_path = '/usr/lib/llvm-current/lib'
let g:clang_user_options='|| exit 0'
let g:clang_complete_auto = 1

" error window
"let g:clang_complete_copen = 1 "open
let g:clang_close_preview = 1  "autoclose
let g:clang_hl_errors = 1      "clang highlite
let g:clang_user_options="-std=c++11"

" snipmate
" let g:clang_snippets_engine = 'snipmate'
" let g:clang_snippets = 1

" complete preprocessoir macros and constants
let g:clang_complete_macros = 1
let g:clang_complete_patterns = 1

"""" clang format
let g:clang_format#command = '/usr/bin/obi-clang-format'
let g:clang_format#style_options = {
            \ "UseTab" : "Never",
            \ "IndentWidth" : 4,
            \ "BreakBeforeBraces" : "Allman",
            \ "IndentCaseLabels": "false",
            \ "ColumnLimit" : 80,
            \ "AccessModifierOffset" : -4,
            \ "AllowShortIfStatementsOnASingleLine" : "false",
            \ "AlwaysBreakTemplateDeclarations" : "true",
            \ "DerivePointerBinding" : "false",
            \ "PointerBindsToType" : "true",
            \ "Standard" : "C++11"}

"BreakBeforeBraces : Allman  "Michi Style
"BreakBeforeBraces : Stroustrup

" map to <Leader>cf in C++ code
" autocmd FileType c,cpp,objc nnoremap <buffer><Leader>cf :<C-u>ClangFormat<CR>
" autocmd FileType c,cpp,objc vnoremap <buffer><Leader>cf :ClangFormat<CR>

" if you install vim-operator-user
augroup clang
    autocmd!
    autocmd FileType c,cpp,objc map <buffer><Leader>cff ggvG<Plug>(operator-clang-format)
    autocmd FileType c,cpp,objc map <buffer><Leader>cf <Plug>(operator-clang-format)
augroup END
