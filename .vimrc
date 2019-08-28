set nocompatible              " be iMproved, required
filetype off                  " required

set exrc
set secure
set number relativenumber
set nu rnu

function! OpenOther()
    if expand("%:e") == "cpp"
        exe "split" fnameescape(expand("%:p:r:s?src?include?").".hpp")
    elseif expand("%:e") == "h"
        exe "split" fnameescape(expand("%:p:r:s?include?src?").".cpp")
    endif
endfunction

nmap ,o :call OpenOther()<CR>

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" dark theme
Plugin 'tomasiser/vim-code-dark'

" toggle header
Plugin 'ericcurtin/CurtineIncSw.vim'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" Git plugin not hosted on GitHub
Plugin 'git://git.wincent.com/command-t.git'
" git repos on your local machine (i.e. when working on your own plugin)
Plugin 'file:///home/gmarik/path/to/plugin'
" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plugin 'ascenator/L9', {'name': 'newL9'}

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
"
colorscheme codedark

set expandtab
set shiftwidth=2
set softtabstop=2

map <C-K> ggVG :py3f /usr/share/clang/clang-format-8/clang-format.py<cr>
imap <C-K> <c-o>:py3f /usr/share/clang/clang-format-8/clang-format.py<cr>

map <Space>c :e %<.cpp<cr>
map <Space>h :e %<.hpp<cr>

