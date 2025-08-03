if has("eval")                    "vim-tiny lacks eval
  let skip_defaults_vim=1
endif

let mapleader = " "

set guicursor=
set ruler
set number
set nocompatible
set modelines=0
set relativenumber
set novisualbell
set cursorline

set hlsearch
set incsearch

set ignorecase
set smartcase
set showmatch

set wildmenu
set wildmode=full

set wrap
set linebreak

set undofile
set noswapfile

set tabstop=2
set shiftwidth=2
set softtabstop=2
set expandtab
set scrolloff=6
set colorcolumn=80

set smartindent
set nowrap

set laststatus=2
set statusline=
set statusline+=\ %f
set statusline+=%m\
set statusline+=%=
set statusline+=%#CursorColumn#
set statusline+=\ %y
set statusline+=\ %{&fileencoding?&fileencoding:&encoding}
set statusline+=\[%{&fileformat}\]
set statusline+=\ %p%%
set statusline+=\ %l:%c
set statusline+=\ 

nnoremap / /\v
vnoremap / /\v

inoremap <F1> <ESC>
nnoremap <F1> <ESC>
vnoremap <F1> <ESC>

vnoremap <S-up> :m '<-2<CR>gv=gv
vnoremap <S-down> :m '>+1<CR>gv=gv

" Navigate by half-screen & scroll.
nnoremap <C-d> <C-d>zz
nnoremap <C-u> <C-u>zz

" Splitting:
set splitbelow
set splitright
nnoremap <C-down> <C-W><C-J>
nnoremap <C-up> <C-W><C-K>
nnoremap <C-right> <C-W><C-L>
nnoremap <C-lefT> <C-W><C-H>

nnoremap <leader>pv :Ex<CR>

nnoremap <leader>y "+y
vnoremap <leader>y "+y
nnoremap <leader>Y "+Y

nnoremap <leader>d "+d
vnoremap <leader>d "+d
nnoremap <leader>D "+D

nnoremap <leader>p "+p
vnoremap <leader>p "+p
nnoremap <leader>P "+P
nnoremap <leader>s :%s/\<<C-r><C-w>\>/<C-r><C-w>/gI<Left><Left><Left>

nnoremap <leader><leader> :so<CR>

exec "set listchars=tab:\uBB\uBB,trail:\uB7,nbsp:~"

set list
map <C-t><up> :tabr<cr>
map <C-t><down> :tabl<cr>
map <C-t><left> :tabp<cr>
map <C-t><right> :tabn<cr>

syntax enable
colorscheme murphy

if has("gui_running")
  set guifont=3270Medium\ NF:h16:cDEFAULT
  set guioptions-=T
  set lines=50
  set columns=90
endif

if has("autocmd")
  autocmd BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g`\"" | endif
  autocmd BufNewFile,BufRead *.kbd :set filetype=lisp
  autocmd FileType yaml setlocal ts=2 sts=2 sw=2 expandtab
endif


let g:indentLine_char = '¦'

