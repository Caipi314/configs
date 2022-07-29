" set nocompatible              " be iMproved, required
" filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'



Plugin 'itchyny/lightline.vim'
Plugin 'shinglyu/vim-codespell'






" git info
" Plugin 'vim-gitgutter'

" Track the engine.
" Plugin 'SirVer/ultisnips'

" Languages

" Plugin 'pangloss/vim-javascript'
" Plugin 'mxw/vim-jsx'

" Snippets are separated from the engine. Add this if you want them:
" Plugin 'honza/vim-snippets'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line



" Bottom bar
set laststatus=2


syntax on

colorscheme molokai
hi MatchParen      ctermfg=208  ctermbg=none cterm=bold



" Spelling
hi SpellBad cterm=none ctermbg=236
:set spell
" run spelling after saving
:autocmd BufWritePre *.* :Codespell

"set termguicolors
set t_Co=256
let g:sublimemonokai_term_italic = 1
" Languages
let java_comment_strings=1
let java_highlight_functions=1
let java_highlight_java_lang_ids=1

" Snippets settings

"   " Trigger configuration. You need to change this to something other than <tab> if you use one of the following:
"   " - https://github.com/Valloric/YouCompleteMe
"   " - https://github.com/nvim-lua/completion-nvim
"   let g:UltiSnipsExpandTrigger="<tab>"
"   let g:UltiSnipsJumpForwardTrigger="<c-b>"
"   let g:UltiSnipsJumpBackwardTrigger="<c-z>"
"   
"   " If you want :UltiSnipsEdit to split your window.
"   let g:UltiSnipsEditSplit="vertical"
"   
"   
" Non plugin settings:
set whichwrap=<,>,h,l

" Causes bad syntax highlighting
"   " Save folds
"   augroup remember_folds
"     autocmd!
"     autocmd BufWinLeave *.* mkview
"     autocmd BufWinEnter *.* silent! loadview
"   augroup END

" ":W" to format current file
:command W !prettier % --write
:command Ww w | W
:command R !sh run.sh
:command Setrun !echo 'java '% > run.sh
" set autoread

set tabstop=2
set softtabstop=2
" when indenting with '>', use 2 spaces width
set shiftwidth=2

" turn cursor to a line
let &t_SI = "\e[5 q"
let &t_EI = "\e[2 q"

" set number
set spr " split to the right by default

" move lines
nnoremap <C-k> :m-2<CR>
nnoremap <C-j> :m+<CR>
inoremap <C-k> <Esc>:m-2<CR>
inoremap <C-j> <Esc>:m+<CR>

" auto complete
map <Nul> <c-space>
map! <Nul> <c-space>
inoremap <c-space> <c-n>

" Paste without copying
xnoremap p "_dP
" Yank into system
vnoremap <C-y> "+y


" File explorer
:command Bar Lexplore!
let g:netrw_banner = 0
let g:netrw_liststyle = 3
let g:netrw_browse_split = 4
let g:netrw_altv = 1
let g:netrw_winsize = 20

" Git gutter
set updatetime=1000
highlight clear SignColumn

" on Startup
