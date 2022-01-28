let mapleader = ","

let maplocalleader = "\\"
"autocmd buffilepre
autocmd FileType c++ nnoremap <buffer> <localleader>c I//<esc>
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

set cursorline 
set shiftwidth=4
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
" Shjjow partial command you type in the last line of the screen.
" set showcmd
"
" Enable auto completion menu after pressing TAB.
set wildmenu

" Make wildmenu behave like similar to Bash completion.
"set wildmode=list:longest
set wildmenu
set wildmode=full

" There are certain files that we would never want to edit with Vim.
" Wildmenu will ignore files with these extensions.
set wildignore=*.docx,*.jpg,*.png,*.gif,*.pdf,*.pyc,*.exe,*.flv,*.img,*.xlsx


" PLUGINS ---------------------------------------------------------------- {{{

call plug#begin('~/.vim/pjsonlugged')

    Plug 'dense-analysis/ale'
    Plug 'voldikss/vim-translator'
    Plug 'preservim/nerdtree'
    Plug 'dracula/vim', { 'as': 'dracula' }
    "Plug 'xavierd/clang_complete' 
    Plug 'ludovicchabant/vim-gutentags'
    Plug 'skywind3000/asyncrun.vim'
    Plug 'octol/vim-cpp-enhanced-highlight'
    Plug 'Yggdroot/LeaderF', { 'do': ':LeaderfInstallCExtension' }
    Plug 'jiangmiao/auto-pairs'
    "Plug 'Valloric/YouCompleteMe'
    Plug 'tpope/vim-surround'
    Plug 'fatih/vim-go'
    Plug 'neoclide/coc.nvim' , {'branch': 'release'}

call plug#end()

" }}}
"
"translator {{{
nmap <silent> <Leader>tw <Plug>TranslateW
vmap <silent> <Leader>tw <Plug>TranslateWV
let g:translator_proxy_url = 'socks5://127.0.0.1:7891'

"}}}
"coc -------->{{{
"}}}
set hidden
let g:coc_global_extensions = ['coc-json','coc-vimlsp']

set updatetime=300
if has("nvim-0.5.0") || has("patch-8.1.1564")
  " Recently vim can merge signcolumn and number column into one
  set signcolumn=number
else
  set signcolumn=yes
endif

inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ <SID>check_back_space() ? "\<TAB>" :
      \ coc#refresh()
inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"

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
" Applying codeAction to the selected region.
" Example: `<leader>aap` for current paragraph
xmap <leader>a  <Plug>(coc-codeaction-selected)
nmap <leader>a  <Plug>(coc-codeaction-selected)
" Remap keys for applying codeAction to the current buffer.
nmap <leader>ac  <Plug>(coc-codeaction)
" Apply AutoFix to problem on the current line.
nmap <leader>qf  <Plug>(coc-fix-current)
" Run the Code Lens action on the current line.
nmap <leader>cl  <Plug>(coc-codelens-action)
" Remap <C-f> and <C-b> for scroll float windows/popups.
if has('nvim-0.4.0') || has('patch-8.2.0750')
  nnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
  nnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
  inoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(1)\<cr>" : "\<Right>"
  inoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? "\<c-r>=coc#float#scroll(0)\<cr>" : "\<Left>"
  vnoremap <silent><nowait><expr> <C-f> coc#float#has_scroll() ? coc#float#scroll(1) : "\<C-f>"
  vnoremap <silent><nowait><expr> <C-b> coc#float#has_scroll() ? coc#float#scroll(0) : "\<C-b>"
endif
" Use CTRL-S for selections ranges.
" Requires 'textDocument/selectionRange' support of language server.
nmap <silent> <leader>s <Plug>(coc-range-select)
xmap <silent> <leader>S <Plug>(coc-range-select)
" Add `:Format` command to format current buffer.
command! -nargs=0 Format :call CocActionAsync('format')

" Add `:Fold` command to fold current buffer.
command! -nargs=? Fold :call     CocAction('fold', <f-args>)

" Add `:OR` command for organize imports of the current buffer.
command! -nargs=0 OR   :call     CocActionAsync('runCommand', 'editor.action.organizeImport')
" Mappings for CoCList
" Show all diagnostics.
nnoremap <silent><nowait> <space>a  :<C-u>CocList diagnostics<cr>
" Manage extensions.
nnoremap <silent><nowait> <space>e  :<C-u>CocList extensions<cr>
" Show commands.
nnoremap <silent><nowait> <space>c  :<C-u>CocList commands<cr>
" Find symbol of current document.
nnoremap <silent><nowait> <space>o  :<C-u>CocList outline<cr>
" Search workspace symbols.
nnoremap <silent><nowait> <space>s  :<C-u>CocList -I symbols<cr>
" Do default action for next item.
nnoremap <silent><nowait> <space>j  :<C-u>CocNext<CR>
" Do default action for previous item.
nnoremap <silent><nowait> <space>k  :<C-u>CocPrev<CR>
" Resume latest coc list.
nnoremap <silent><nowait> <space>p  :<C-u>CocListResume<CR>

nnoremap <silent><leader>h  :call <SID>show_documentation()<CR>

function! s:show_documentation()
  if (index(['vim','help'], &filetype) >= 0)
    execute 'h '.expand('<cword>')
  elseif (coc#rpc#ready())
    call CocActionAsync('doHover')
  else
    execute '!' . &keywordprg . " " . expand('<cword>')
  endif
endfunction


" to disable vim-go gd function
" disable vim-go :GoDef short cut (gd)
" this is handled by LanguageClient [LC]
let g:go_def_mapping_enabled = 0
let g:go_code_completion_enabled = 0


"}}}
"

" color theme ------->{{{
colorscheme dracula
" }}}
"
let g:clang_use_library = 1
let g:clang_library_path='/usr/lib/llvm-12/lib/libclang.so.1' 

"------------->gutentags
"
let g:gutentags_project_root = ['.root', '.svn', '.git', '.hg', '.project']

"-------------> asynrun

let g:asyncrun_open = 6
nnoremap <F10> :call asyncrun#quickfix_toggle(6)<cr>
nnoremap <silent> <F9> :AsyncRun g++ -std=c++11 -Wall -O2 "$(VIM_FILEPATH)" -o "$(VIM_FILEDIR)/$(VIM_FILENOEXT)" <cr>
" 递归查找包含该目录的目录作为根目录，若找不到则将文件所在目录作为当前目录
let g:asyncrun_rootmarks = ['.svn', '.git', '.root', '_darcs', 'build.xml'] 
" 设置 F7 编译项目
nnoremap <silent> <F7> :AsyncRun -cwd=<root> make <cr>
" 设置 F5 运行当前程序
"nnoremap <silent> <F5> :AsyncRun -raw -cwd=$(VIM_FILEDIR) "$(VIM_FILEDIR)/$(VIM_FILENOEXT)" <cr>
nnoremap <silent> <F5> :AsyncRun g++ -std=c++17 -Wall "$(VIM_FILEPATH)" && ./a.out <cr>"

"-----------> cpp highlight
"
let g:cpp_experimental_template_highlight = 1
let g:cpp_posix_standard = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_class_scope_highlight = 1



"" 所生成的数据文件的名称
let g:gutentags_ctags_tagfile = '.tags'

" 将自动生成的 tags 文件全部放入 ~/.cache/tags 目录中，避免污染工程目录
let s:vim_tags = expand('~/.cache/tags')
let g:gutentags_cache_dir = s:vim_tags

" 配置 ctags 的参数
let g:gutentags_ctags_extra_args = ['--fields=+niazS', '--extra=+q']
let g:gutentags_ctags_extra_args += ['--c++-kinds=+px']
let g:gutentags_ctags_extra_args += ['--c-kinds=+px']
" 
"
"
"
"-------------------->ale
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

"-------------------> ycmk
"let g:ycm_key_list_select_completion = ['<Down>']
"let g:ycm_key_list_previous_completion = ['<Up>']
"let g:ycm_key_list_stop_completion = ['<C-Y']
"
"let g:ycm_goto_buffer_command = 'horizontal-split'
"let g:ycm_server_python_interpreter='/usr/bin/python3'
"let g:ycm_global_ycm_extra_conf = '~/.vim/.ycm_extra_conf.py'
"let g:airline#extensions#tabline#enabled = 1
"let g:ycm_seed_identifiers_with_syntax = 1
"let g:ycm_complete_in_strings = 1
"let g:ycm_collect_identifiers_from_tags_files = 1
"let g:ycm_complete_in_comments = 1
"let g:ycm_min_num_of_chars_fo=0
"let g:ycm_confirm_extra_conf = 0
""
"
nnoremap <c-j> <c-w><c-j>
nnoremap <c-k> <c-w><c-k>
nnoremap <c-h> <c-w><c-h>
nnoremap <c-l> <c-w><c-l>

inoremap jj <esc>
nnoremap <leader>\ :nohlsearch<CR>
nnoremap <leader>n :bn<CR>
nnoremap <leader>p :bp<CR>
nnoremap <leader>q :q<CR>
nnoremap <leader>qw :wq<CR>
nnoremap <leader>sa ggVG
nnoremap <leader>qo :copen<CR>
nnoremap <leader>qc :cclose<CR>
nnoremap <leader>qn :cNext<CR>
nnoremap <leader>qp :cprevious<CR>
nnoremap <leader>fn :Leaderf function<CR>
nnoremap <C-x>  <C-v>
nnoremap <leader>ev :split $MYVIMRC<cr>
nnoremap <leader>sv :source $MYVIMRC<cr>
nnoremap <leader>; :execute "normal! mqA;\e`q"<cr>
nnoremap H ^
nnoremap L $


" plug map
"--> nerd tree <--
"nnoremap <leader>n :NERDTreeFocus<CR>
"nnoremap <C-n> :NERDTree<CR>
nnoremap <leader><leader> :NERDTreeToggle<CR>
"nnoremap <C-f> :NERDTreeFind<CR>

"---> clang-complete
"

onoremap in(  :<c-u>normal! f(vi(<cr>
onoremap il(  :<c-u>normal! F)vi(<cr>


" }}}
