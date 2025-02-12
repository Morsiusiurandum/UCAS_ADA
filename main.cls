\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{main}[2024/11/17 Style Class]

% 加载基础类
\LoadClass[10pt, a4paper, oneside]{ctexrep}

% 加载必要的包
\RequirePackage[a4paper,margin=0.7in]{geometry}
\RequirePackage{minted,algorithm,amsmath,amsthm,amssymb,bm,xcolor,framed,graphicx,hyperref,mathrsfs}
\RequirePackage{tikz,tikz-qtree,multirow,ulem,microtype,longtable,algpseudocode}

% 页面样式设置
\pagestyle{empty}
\newcommand{\defaultauthor}{Morsiusiurandum}
\linespread{1.5}

% 定义自定义环境
\definecolor{shadecolor}{RGB}{240,240,240}
\newcounter{problem}

\newenvironment{problem}
    {
        \refstepcounter{problem} % 递增计数器
        \begin{shaded} % 使用 shaded 让内容有背景
        \noindent\textbf{问题 \theproblem} % 显示编号
        \newline
        \addcontentsline{toc}{subsection}{问题 \theproblem} % 添加到目录 
    }
    {\end{shaded}\par}

\newenvironment{solution}
{\par\noindent\textbf{解答.}\newline}
{\par\vspace{1cm}}

% 设置段落样式
\setlength{\parindent}{0pt}

