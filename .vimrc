" --------
"  Vim Plug
"  -------
let data_dir = has('nvim') ? stdpath('data') . '/site' : '~/.vim'
if empty(glob(data_dir . '/autoload/plug.vim'))
  silent execute '!curl -fLo '.data_dir.'/autoload/plug.vim --create-dirs  https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
  autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif
" ------------------
" Appearances --
" ------------------

" Turn on syntax highlighting.
set nocompatible

" ------------------
" syntax and indent
" ------------------

syntax on " turn on syntax highlighting
set showmatch " show matching braces when text indicator is over them
" making it easier to see the matches parenthesese etc.
hi MatchParen cterm=bold ctermbg=red ctermfg=red

" Exit Vim if NERDTree is the only window remaining in the only tab.
autocmd BufEnter * if tabpagenr('$') == 1 && winnr('$') == 1 && exists('b:NERDTree') && b:NERDTree.isTabTree() | quit | endif

" highlight current line, but only in active window
augroup cursorlineonlyinactivewindow
    autocmd!
    autocmd vimenter,winenter,bufwinenter * setlocal cursorline
    autocmd winleave * setlocal nocursorline
augroup end

filetype plugin indent on " enable file type detection
runtime macros/matchit.vim

set autoindent
set formatoptions-=cro


"---------------------
" basic editing config
"---------------------

set shortmess+=i " disable the default vim startup message.
set number " show line numbers.
" this enables relative line numbering mode. with both number and
" relativenumber enabled, the current line shows the true line number, while
" all other lines (above and below) are numbered relative to the current line.
" this is useful because you can tell, at a glance, what count is needed to
" jump up or down to a particular line, by {count}k to go up or {count}j to go
" down.
" set relativenumber " always show the status line at the bottom, even if you only have one window open.
set laststatus=2
" the backspace key has slightly unintuitive behavior by default. for example,
" by default, you can't backspace before the insertion point set with 'i'.
" this configuration makes backspace behave more reasonably, in that you can
" backspace over anything.
set backspace=indent,eol,start
" by default, vim doesn't let you hide a buffer (i.e. have a buffer that isn't
" shown in any window) that has unsaved changes. this is to prevent you from "
" forgetting about unsaved changes and then quitting e.g. via `:qa!`. we find
" hidden buffers helpful enough to disable this protection. see `:help hidden`
" for more information on this.
set hidden
" this setting makes search case-insensitive when all characters in the string
" being searched are lowercase. however, the search becomes case-sensitive if
" it contains any capital letters. this makes searching more convenient.

" enable searching as you type, rather than waiting till you press enter.
set ignorecase
set smartcase 
set incsearch " unbind some useless/annoying default key bindings.
" enable mouse support. you should avoid relying on this too much, but it can
" sometimes be convenient.
set mouse+=a
set timeout timeoutlen=1000 ttimeoutlen=100 " fix slow 0 inserts
set lazyredraw " skip redrawing screen in some cases
set autochdir " automatically set current directory to directory of last opened file
set history=8192 " more history
set nojoinspaces " suppress inserting two spaces between sentences
" use 4 spaces instead of tab during formatting
set expandtab 
set tabstop=4
set shiftwidth=4
set softtabstop=4
" tab completion for files/bufferss
set wildmode=longest,list
set wildmenu
if &term =~ '^screen'
" tmux knows the extended mouse mode
set ttymouse=xterm2
endif
set nofoldenable " disable folding by default
let $VIM='~/.vim/'
set modifiable

"--------------------
" misc configurations
"--------------------

set noerrorbells visualbell t_vb= " disable audible bell because it's annoying.

" open new split panes to right and bottom, which feels more natural
set splitbelow
set splitright

"mapping leader and local leader
let mapleader = " "
let maplocalleader = "\\"

" Plug 'sirver/ultisnips'
"directory and use of vim plugin vim-plug
call plug#begin('~/.vim/plugged')
Plug 'leafgarland/typescript-vim'
Plug 'pangloss/vim-javascript'
 Plug 'chrisbra/csv.vim'
Plug 'yuezk/vim-js'
Plug 'maxmellon/vim-jsx-pretty'
Plug 'honza/vim-snippets'
Plug 'tpope/vim-fugitive'
Plug 'morhetz/gruvbox'
Plug 'tpope/vim-surround'
Plug 'vim-scripts/dbext.vim'
Plug 'kana/vim-textobj-user'
Plug 'kana/vim-textobj-entire'
Plug 'kien/ctrlp.vim'
Plug 'bps/vim-textobj-python'
Plug 'tpope/vim-commentary'
Plug 'dense-analysis/ale'
call plug#end()


syntax enable
set background=dark
colorscheme gruvbox
" if strftime ('%H') > 22 
"     colorscheme gruvbox
"     set background=dark
" elseif strftime ('%H') < 7
"     colorscheme gruvbox
"     set background=dark
" elseif strftime ('%H') > 16
"     colorscheme solarized
"     set background=dark
" else
"     colorscheme solarized
"     set background=light
" endif

" try to prevent bad habits like using the arrow keys for movement. this is
" not the only possible bad habit. for example, holding down the h/j/k/l keys
" for movement, rather than using more efficient movement commands, is also a
" bad habit. the former is enforceable through a .vimrc, while we don't know
" how to prevent the latter.
" do this in normal mode...
nnoremap <left>  :echoe "use h"<cr>
nnoremap <right> :echoe "use l"<cr>
nnoremap <up>    :echoe "use k"<cr>
nnoremap <down>  :echoe "use j"<cr>
" ...and in insert mode
inoremap <left>  <esc>:echoe "use h"<cr>
inoremap <right> <esc>:echoe "use l"<cr>
inoremap <up>    <esc>:echoe "use k"<cr>
inoremap <down>  <esc>:echoe "use j"<cr>

" I'm setting up movement keys
nnoremap <leader>j <c-w>j
nnoremap <leader>k <c-w>k
nnoremap <leader>l <c-w>l
nnoremap <leader>h <c-w>h

" copy to clipboard
vnoremap <leader>y "+y



"some vimscript practice

noremap <leader>-      0v$y<esc>dd<esc>p
noremap <leader>_      0v$y<esc>dd<esc>kkp
noremap <leader><c-u>  viwu


" I want to make it so I can jump to a place and have it centered rather
" easily
" nnoremap  <space> ggzz

" mapping H and L for more sensible move to start and end of line binds
nnoremap L $
nnoremap H 0
nnoremap U H
nnoremap D L


"making it so i can access vimrc quickly from vim
nnoremap <leader>ev :vsplit ~/.vimrc<cr>
nnoremap <leader>sv :source ~/.vimrc<cr> 


set showcmd



" for all buffers
let g:slime_target = "tmux"
let g:slime_bracketed_paste = 1



"---------------------
" Plugin configuration
"---------------------

" nerdtree ------------------
" nnoremap <Leader>n :NERDTreeToggle<CR>
" nnoremap <Leader>f :NERDTreeFind<CR>



" ultisnips -----------------------
let g:UltiSnipsExpandTrigger       = '<Tab>'    " use Tab to expand snippets
let g:UltiSnipsJumpForwardTrigger  = 'jk'    " use jk to move forward through tabstops
let g:UltiSnipsJumpBackwardTrigger = '<S-Tab>'  " use Shift-Tab to move backward through tabstops

" psql? --------------------
au BufRead /tmp/psql.edit.* set syntax=sql
let g:dbext_default_profile_postgres ='type=PGSQL:user=postgres:dbname=tysql'
let g:dbext_default_profile = 'postgres'

"R has a weird problem converting _ to <--
let R_assign_map = "|"

" vimtex -------------------------
" Use `<localleader>c` to trigger continuous compilation...
" nmap <localleader>c <Plug>(vimtex-compile)

" ...or single-shot compilation, if you prefer.
nmap <leader>c <Plug>(vimtex-compile-ss)

" Use <leader>ss in normal mode to refresh UltiSnips snippets
nnoremap <localleader>s <Cmd>call UltiSnips#RefreshSnippets()<CR>

" ale --------------------
" Error shown only when on the line
let g:ale_virtualtext_cursor = 'current'
" Virtual text color
highlight ALEVirtualTextError ctermfg=Black
" the sign in the sign gutter
let g:ale_sign_error = "X"
let g:ale_sign_warning = "W"
" sign gutter alway on
let g:ale_sign_column_always = 1
" sign column color
highlight clear SignColumn
highlight ALEErrorSign ctermbg=NONE ctermfg=red
highlight ALEWarningSign ctermbg=NONE ctermfg=yellow
" 
"enable python linter 
" let g:ale_linters = {
"     \ 'javascript': ['prettier','eslint'],
"     \ 'python': ['pyflakes'],
"     \ 'cpp': ['g++'] 
"     \}

"ctrlp mapping ----------------------
" let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'ctrlp'
" nnoremap <leader>p :CtrlP<cr>
" inoremap <C-p> <esc>:echoe "wrong"<cr><esc>:startinsert<cr>

" running python in vim --------------------
autocmd FileType python map <buffer> <F9> :w<CR>:exec '!python3' shellescape(@%, 1)<CR>
autocmd FileType python imap <buffer> <F9> <esc>:w<CR>:exec '!python3' shellescape(@%, 1)<CR>

" running anybot command in vim --------------------
autocmd FileType html map <buffer> <F9> :w<CR>:exec '!brew services restart httpd' <CR>
autocmd FileType html imap <buffer> <F9> <esc>:w<CR>:exec '!brew services restart httpd' <CR>


" running haskell on vim? -------------------
autocmd FileType haskell map <buffer> <F9> :w<CR>:exec '!ghc' shellescape(@%, 1)<CR>
autocmd FileType haskell imap <buffer> <F9> <esc>:w<CR>:exec '!ghc' shellescape(@%, 1)<CR>

" running cpp on vim? -------------------
autocmd FileType cpp map <buffer> <F9> :w<CR>:exec '!g++' shellescape(@%, 1)<CR>
autocmd FileType cpp imap <buffer> <F9> <esc>:w<CR>:exec '!g++' shellescape(@%, 1)<CR>

" running javascript on vim -------------------
autocmd FileType javascript setlocal shiftwidth=2 tabstop=2 expandtab softtabstop=2

" ocaml compatibility --------  
set rtp^="/home/reiro/.opam/default/share/ocp-indent/vim"

"Treat .c0 files as C --------
augroup c0_files
    autocmd!
    autocmd BufRead,BufNewFile *.c0 setfiletype c
    autocmd FileType c let b:ale_enabled = 0
augroup END
