">>>>>>>temp{{{

map <F1> :call Runtermdebug()<CR>
func! Runtermdebug()
exec "w"
if &filetype == 'c'
    exec "!gcc % -g -o %<"
elseif &filetype == 'cpp'
    exec "!g++ % -g -o %<"
endif
exec "packadd termdebug"
exec "Termdebug %<"
endfunc

au filetype cpp nnoremap <silent> <F5> :AsyncRun g++ -std=c++17 -Wall "$(VIM_FILEPATH)" && ./a.out <cr>"

let $GTAGSLABEL = 'native-pygments'
let $GTAGSCONF = '/usr/local/share/gtags/gtags.conf'


"set shortmess=a
set cmdheight=1

abbreviate W w
abbreviate Q q

function! LoadView() abort
try
    loadview
catch /E484/
    return
endtry
endfunction

tnoremap <m-[> <c-\><c-n>

set foldmethod=manual
"au bufwinleave ?*  silent mkview
"au bufwinenter ?* call LoadView()
"au BufWinLeave ?* mkview
"au BufWinEnter ?* silent! loadview
augroup AutoSaveGroup
    autocmd!
    " view files are about 500 bytes
    " bufleave but not bufwinleave captures closing 2nd tab
    " nested is needed by bufwrite* (if triggered via other autocmd)
    " BufHidden for compatibility with `set hidden`
    autocmd BufWinLeave,BufLeave,BufWritePost,BufHidden,QuitPre ?* nested silent! mkview!
    autocmd BufWinEnter ?* silent! loadview
augroup end
au filetype rust  nnoremap<f5> :AsyncRun cargo run <CR>

nnoremap tn :tabn<cr>
nnoremap tp :tabp<cr>
nnoremap tc :tabc<cr>


"}}}


"--->basic config{{{
"

set hidden
let mapleader = ","

let maplocalleader = "\\"
"autocmd buffilepre
autocmd filetype c++ nnoremap <buffer> <localleader>c i//<esc>
"disable compitablity with vi
"
set nocompatible
" dectype file type
filetype on

filetype plugin on
filetype indent on


syntax on
set number
set noswapfile

set autochdir
set cursorline
set shiftwidth=4
autocmd filetype cpp :set shiftwidth=2
set tabstop=4
set expandtab
set nobackup

set scrolloff=10
set nowrap

set incsearch
set ignorecase
set smartcase
set showmatch
set hlsearch

" ban warning bell

set noerrorbells
set novisualbell


set tags=./.tags;,.tags
set tags+=./tags

set path+=/usr/include/c++/9
set path+=/use/local/include
" shjjow partial command you type in the last line of the screen.
" set showcmd
"
" enable auto completion menu after pressing tab.
set wildmenu

" make wildmenu behave like similar to bash completion.
"set wildmode=list:longest
set wildmenu
set wildmode=full

" there are certain files that we would never want to edit with vim.
" wildmenu will ignore files with these extensions.
set wildignore=*.docx,*.jpg,*.png,*.gif,*.pdf,*.pyc,*.exe,*.flv,*.img,*.xlsx



"
"}}}

" plugins ---------------------------------------------------------------- {{{

call plug#begin('~/.vim/pjsonlugged')

    "=========> vim theme <======
    Plug 'trevordmiller/nova-vim'
    Plug 'preservim/vim-colors-pencil'
    Plug 'soft-aesthetic/soft-era-vim'
    Plug 'kaicataldo/material.vim', { 'branch': 'main' }
    Plug 'morhetz/gruvbox'
    Plug 'flazz/vim-colorschemes'

    "=========> vim theme <======





    Plug 'dense-analysis/ale'
    Plug 'voldikss/vim-translator'
    Plug 'preservim/nerdtree'
    "Plug 'dracula/vim', { 'as': 'dracula' }
    "plug 'xavierd/clang_complete'
    "Plug 'kyoz/purify'
    "Plug 'sonph/onehalf', { 'rtp': 'vim' }
    Plug 'arcticicestudio/nord-vim'
    Plug 'ludovicchabant/vim-gutentags'
    Plug 'skywind3000/asyncrun.vim'
    Plug 'octol/vim-cpp-enhanced-highlight'
    Plug 'yggdroot/leaderf', { 'do': ':leaderfinstallcextension' }
    Plug 'jiangmiao/auto-pairs'
    "plug 'valloric/youcompleteme'
    Plug 'tpope/vim-surround'
    Plug 'fatih/vim-go'
    Plug 'neoclide/coc.nvim' , {'branch': 'release'}
    Plug 'Chiel92/vim-autoformat'
    Plug 'preservim/nerdcommenter'
    Plug 'itchyny/lightline.vim'
    "plug 'junegunn/fzf', { 'do': { -> fzf#install() } }>
    Plug 'junegunn/fzf'
    Plug 'junegunn/fzf.vim'
    Plug 'mhinz/vim-startify'
    Plug 'voldikss/vim-floaterm'
    Plug 'voldikss/LeaderF-floaterm'
    Plug 'majutsushi/tagbar'





call plug#end()

" }}}


"--->plug config{{{
"=============>lightline<====================
let g:lightline = {
            \ 'colorscheme': 'powerlineish',
            \ }

"=============>lightline<====================

"=============>autoformat<====================

"unmap <c-w>
noremap  <f3> :Autoformat<cr>
let g:autoformat_verbosemode=1
"保存时自动格式化php代码
"au bufwrite *.cc  :autoformat
"au bufwrite *.h  :autoformat


"=============>autoformat<====================

"=============>translator<====================

nmap <silent> <leader>tw <plug>translatew
vmap <silent> <leader>tw <plug>translatewv
let g:translator_proxy_url = 'socks5://127.0.0.1:7891'


"=============>translator<====================

"=============>cocnvim<====================

nnoremap <leader>qf :Cocfix<cr>
let g:coc_global_extensions = ['']

set updatetime=300
if has("nvim-0.5.0") || has("patch-8.1.1564")
    " recently vim can merge signcolumn and number column into one
    set signcolumn=number
else
    set signcolumn=yes
endif

inoremap <silent><expr> <tab>
            \ pumvisible() ? "\<c-n>" :
            \ <sid>check_back_space() ? "\<tab>" :
            \ coc#refresh()
inoremap <expr><s-tab> pumvisible() ? "\<c-p>" : "\<c-h>"

function! s:check_back_space() abort
let col = col('.') - 1
return !col || getline('.')[col - 1]  =~# '\s'
endfunction

inoremap <silent><expr> <c-space> coc#refresh()
nmap <silent> <M-[> <Plug>(coc-diagnostic-prev)
nmap <silent> <M-]> <Plug>(coc-diagnostic-next)
nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)
nmap <leader>rn <Plug>(coc-rename)
xmap <leader>f  <Plug>(coc-format-selected)
nmap <leader>f  <Plug>(coc-format-selected)
augroup mygroup
    autocmd!
    " Setup formatexpr specified filetype(s).
    autocmd FileType typescript,json setl formatexpr=CocAction('formatSelected')
    " Update signature help on jump placeholder.
    autocmd User CocJumpPlaceholder call CocActionAsync('showSignatureHelp')
augroup end
" applying codeaction to the selected region.
" example: `<leader>aap` for current paragraph
" Applying codeAction to the selected region.
" Example: `<leader>aap` for current paragraph
xmap <leader>a  <Plug>(coc-codeaction-selected)
nmap <leader>a  <Plug>(coc-codeaction-selected)
" Remap keys for applying codeAction to the current buffer.
nmap <leader>ac  <Plug>(coc-codeaction)
" Apply AutoFix to problem on the current line.
nmap <leader>qf  <Plug>(coc-fix-current)
" Run the Code Lens action on the current line.                                      nmap <leader>cl  <Plug>(coc-codelens-action)
" Remap <C-f> and <C-b> for scroll float windows/popups.
if has('nvim-0.4.0') || has('patch-8.2.0750')
    nnoremap <silent><nowait><expr> <c-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<c-f>"
    nnoremap <silent><nowait><expr> <c-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<c-b>"
    inoremap <silent><nowait><expr> <c-f> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(1)\<cr>" : "\<right>"
    inoremap <silent><nowait><expr> <c-b> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(0)\<cr>" : "\<left>"
    vnoremap <silent><nowait><expr> <c-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<c-f>"
    vnoremap <silent><nowait><expr> <c-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<c-b>"
endif
" use ctrl-s for selections ranges.
" requires 'textdocument/selectionrange' support of language server.
nmap <silent> <leader>s <plug>(coc-range-select)
xmap <silent> <leader>s <plug>(coc-range-select)
" add `:format` command to format current buffer.
command! -nargs=0 Format :call CocActionAsync('format')

" add `:fold` command to fold current buffer.
command! -nargs=? Fold :call     CocAction('fold', <f-args>)

" add `:or` command for organize imports of the current buffer.
command! -nargs=0 OR   :call     CocActionAsync('runcommand', 'editor.action.organizeimport')
nnoremap <silent><leader>h  :call <sid>show_documentation()<cr>

function! s:show_documentation()
if (index(['vim','help'], &filetype) >= 0)
    execute 'h '.expand('<cword>')
elseif (coc#rpc#ready())
    call CocActionAsync('dohover')
else
    execute '!' . &keywordprg . " " . expand('<cword>')
endif
endfunction


" to disable vim-go gd function
" disable vim-go :godef short cut (gd)
" this is handled by languageclient [lc]
let g:go_def_mapping_enabled = 0
let g:go_code_completion_enabled = 0


let g:clang_use_library = 1
let g:clang_library_path='/usr/lib/llvm-12/lib/libclang.so.1'

"=============>cocnvim<====================

"=============>coclortheme<====================

colorscheme material
set termguicolors
"=============>coclortheme<====================

"=============>coclortheme<====================


"=============>coclortheme<====================



"=============>map for coc-fzf-preview<====================

"xmap <Leader>f [fzf-p]

"nnoremap <silent> [fzf-p]p     :<C-u>CocCommand fzf-preview.FromResources project_mru git<CR>
"nnoremap <silent> [fzf-p]gs    :<C-u>CocCommand fzf-preview.GitStatus<CR>
"nnoremap <silent> [fzf-p]ga    :<C-u>CocCommand fzf-preview.GitActions<CR>
"nnoremap <silent> [fzf-p]b     :<C-u>CocCommand fzf-preview.Buffers<CR>
"nnoremap <silent> [fzf-p]B     :<C-u>CocCommand fzf-preview.AllBuffers<CR>
"nnoremap <silent> [fzf-p]o     :<C-u>CocCommand fzf-preview.FromResources buffer project_mru<CR>
"nnoremap <silent> [fzf-p]<C-o> :<C-u>CocCommand fzf-preview.Jumps<CR>
"nnoremap <silent> [fzf-p]g;    :<C-u>CocCommand fzf-preview.Changes<CR>
"nnoremap <silent> [fzf-p]/     :<C-u>CocCommand fzf-preview.Lines --add-fzf-arg=--no-sort --add-fzf-arg=--query="'"<CR>
"nnoremap <silent> [fzf-p]*     :<C-u>CocCommand fzf-preview.Lines --add-fzf-arg=--no-sort --add-fzf-arg=--query="'<C-r>=expand('<cword>')<CR>"<CR>
"nnoremap          [fzf-p]gr    :<C-u>CocCommand fzf-preview.ProjectGrep<Space>
"xnoremap          [fzf-p]gr    "sy:CocCommand   fzf-preview.ProjectGrep<Space>-F<Space>"<C-r>=substitute(substitute(@s, '\n', '', 'g'), '/', '\\/', 'g')<CR>"
"nnoremap <silent> [fzf-p]t     :<C-u>CocCommand fzf-preview.BufferTags<CR>
"nnoremap <silent> [fzf-p]q     :<C-u>CocCommand fzf-preview.QuickFix<CR>
"nnoremap <silent> [fzf-p]l     :<C-u>CocCommand fzf-preview.LocationList<CR>


"=============>map for coc-fzf-preview<====================


"=============>asynrun<====================
let g:asyncrun_open = 6
nnoremap <F10> :call asyncrun#quickfix_toggle(6)<cr>
nnoremap <silent> <F9> :AsyncRun g++ -std=c++11 -Wall -O2 "$(VIM_FILEPATH)" -o "$(VIM_FILEDIR)/$(VIM_FILENOEXT)" <cr>
" 递归查找包含该目录的目录作为根目录，若找不到则将文件所在目录作为当前目录
let g:asyncrun_rootmarks = ['.svn', '.git', '.root', '_darcs', 'build.xml']
" 设置 F7 编译项目
nnoremap <silent> <F7> :AsyncRun -cwd=<root> make <cr>
" 设置 F5 运行当前程序
"nnoremap <silent> <F5> :AsyncRun -raw -cwd=$(VIM_FILEDIR) "$(VIM_FILEDIR)/$(VIM_FILENOEXT)" <cr>
"nnoremap <silent> <F5> :AsyncRun g++ -std=c++17 -Wall "$(VIM_FILEPATH)" && ./a.out <cr>"

"=============>asynrun<====================

"=============>cpp highlight<====================
let g:cpp_experimental_template_highlight = 1
let g:cpp_posix_standard = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_class_scope_highlight = 1
let g:cpp_class_decl_highlight = 1
let g:cpp_posix_standard = 1

"=============>cpp highlight<====================

"=============>gutentags_ctags<====================
let g:gutentags_project_root = ['.root', '.svn', '.git', '.hg', '.project']
"" 所生成的数据文件的名称
let g:gutentags_ctags_tagfile = '.tags'

" 将自动生成的 tags 文件全部放入 ~/.cache/tags 目录中，避免污染工程目录
let g:gutentags_modules = []
if executable('ctags')
    let g:gutentags_modules += ['ctags']
endif
if executable('gtags-cscope') && executable('gtags')
    let g:gutentags_modules += ['gtags_cscope']
endif


let s:vim_tags = expand('~/.cache/tags')
let g:gutentags_cache_dir = s:vim_tags

" 配置 ctags 的参数
let g:gutentags_ctags_extra_args = ['--fields=+niazS', '--extra=+q']
let g:gutentags_ctags_extra_args += ['--c++-kinds=+px']
let g:gutentags_ctags_extra_args += ['--c-kinds=+px']

let g:gutentags_auto_add_gtags_cscope = 0
"=============>gutentags_ctags<====================

"=============>ale<====================
let g:ale_linters_explicit = 1
let g:ale_completion_delay = 500
let g:ale_echo_delay = 20
let g:ale_lint_delay = 500
let g:ale_echo_msg_format = '[%linter%] %code: %%s'
let g:ale_lint_on_text_changed = 'normal'
let g:ale_lint_on_insert_leave = 1
let g:airline#extensions#ale#enabled = 1

let g:ale_c_gcc_options = '-Wall -O2 -std=c99'
let g:ale_cpp_gcc_options = '-Wall -O2 -std=c++14'
let g:ale_c_cppcheck_options = ''
let g:ale_cpp_cppcheck_options = ''
nnoremap sp <Plug>(ale_previous_wrap)
nnoremap sp <Plug>(ale_next_wrap)
"=============>ale<====================

"=============>floaterm<====================
let g:floaterm_width=0.9
"
"=============>floaterm<====================
"=============>tagbar<====================
"
let g:tagbar_autofocus=1
let g:tagbar_sort=0
let g:tagbar_silent=1
"
"=============>tagbar<====================
"}}}


"---> key map{{{
"

tnoremap <esc> <c-\><c-n>
nnoremap <leader>vtm :split term://bash<cr>
nnoremap <leader>tm :term<cr>
nnoremap <c-j> <c-w><c-j>
nnoremap <c-k> <c-w><c-k>
nnoremap <c-h> <c-w><c-h>
nnoremap <c-l> <c-w><c-l>
nnoremap <silent> <leader>h :call CocActionAsync('doHover')<CR>
xnoremap <leader>ad :CocCommand cSpell.addWordToDictionary<cr>

inoremap jj <esc>
nnoremap <leader>\ :nohlsearch<CR>
nnoremap <leader>n :bn<CR>
nnoremap <leader>p :bp<CR>
nnoremap <leader>q :q<CR>
nnoremap <leader>qa :wqall<CR>
nnoremap <leader>wq :wq<CR>
nnoremap <leader>sa ggVG
nnoremap <leader>st :Startify<cr>
nnoremap <space>qo :copen<CR>
nnoremap <space>qc :cclose<CR>
nnoremap <space>qn :cNext<CR>
nnoremap <space>qp :cprevious<CR>
nnoremap <space>l   :BLines<cr>
nnoremap <space>L   :Lines<cr>
nnoremap <space>t   :BTags<cr>
nnoremap <space>T   :Tags<cr>
nnoremap <space>h   :History<cr>
nnoremap <space>r   :Rg<cr>
nnoremap <space>b   :Buffers<cr>
nnoremap <space>p   :Helptags<cr>
nnoremap <space>F   :Files<cr>

nnoremap <space>fn :Leaderf function<CR>
nnoremap <space>ff   :Leaderf file<cr>
nnoremap <space>fr   :Leaderf rg<cr>
nnoremap <space>fb   :Leaderf buffer<cr>
nnoremap <space>ft   :Leaderf bufTag<cr>
nnoremap <space>fT   :Leaderf tag<cr>
nnoremap <space>fh   :Leaderf mru<cr>
nnoremap <space>fH   :Leaderf mru --cwd<cr>
nnoremap <space>fl   :Leaderf line<cr>
nnoremap <space>fL   :Leaderf line<cr>
nnoremap <space>fs   :Leaderf self<cr>
nnoremap <space>fc   :Leaderf command<cr>
nnoremap <space>fw   :Leaderf floaterm<cr>

tnoremap <silent> <space>wt  <C-\><C-n>:FloatermToggle<CR>
nnoremap <silent> <space>wt  :FloatermToggle<CR>
"tnoremap <silent> <space>ww  <aleC-\><C-n>:FloatermToggle<CR>
tnoremap <silent> <space>wn  <C-\><C-n>:FloatermNext<CR>
tnoremap <silent> <space>wp  <C-\><C-n>:FloatermPrev<CR>
tnoremap <silent> <space>wk  <C-\><C-n>:FloatermKill<CR>
nnoremap <silent> <space>wc  :FloatermNew<CR>
nnoremap <space>k :tabn<CR>
nnoremap <space>j :tabp<CR>


nnoremap \\  :TagbarToggle<CR>

nnoremap <C-x>  <C-v>
nnoremap <leader>mc :CocCommand document.renameCurrentWord<CR>     
nnoremap <leader>ev :split $MYVIMRC<cr>
nnoremap <leader>sv :source $MYVIMRC<cr>
nnoremap <leader>; :execute "normal! mqA;\e`q"<cr>

" mappings for coclist
" show all diagnostics.
nnoremap <silent><nowait> <space>a  :<c-u>CocList diagnostics<cr>
" manage extensions.
nnoremap <silent><nowait> <space>e  :<c-u>CocList extensions<cr>
" show commands.
nnoremap <silent><nowait> <space>c  :<c-u>CocList commands<cr>
" find symbol of current documeno;
"nnoremap <silent><nowait> <space>o  :<c-u>CocList outline<cr>
" search workspace symbols.
"nnoremap <silent><nowait> <space>s  :<c-u>CocList -I symbols<cr>
" do default action for next item.
"nnoremap <silent><nowait> <space>j  :<c-u>Cocnext<cr>
" do default action for previous item.
"nnoremap <silent><nowait> <space>k  :<c-u>Cocprev<cr>
" resume latest Coc List.
"nnoremap <silent><nowait> <space>p  :<c-u>CoclistResume<cr>

nnoremap H ^
nnoremap L $


" plug map
"--> nerd tree <--
"nnoremap <leader>n :NERDTreeFocus<CR>
nnoremap <C-n> :NERDTree<CR>
nnoremap <leader><leader> :NERDTreeToggle<CR>
"nnoremap <C-f> :NERDTreeFind<CR>

"---> clang-complete
"

onoremap in(  :<c-u>normal! f(vi(<cr>
onoremap il(  :<c-u>normal! F)vi(<cr>


"}}}
