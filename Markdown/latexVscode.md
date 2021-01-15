<font face ="Consolas">
<center>LATEX AND VSCODE</center>
</font>
# 安装texlive
$\Delta$ <font face ="方正苏新诗柳楷简体">可以在下列的网址中下载texlive</font>

1. [华为云下载](https://link.zhihu.com/?target=https%3A//mirrors.huaweicloud.com/CTAN/systems/texlive/Images/)
2. [阿里云下载](https://link.zhihu.com/?target=https%3A//mirrors.aliyun.com/CTAN/systems/texlive/Images/)

 - 右键 install-tl-windows，单击以管理员身份运行，进入安装界面，点击左下角的“Advanced”进入高级安装来取消你不需要安装的宏包。

![](https://pic4.zhimg.com/80/v2-11b81c477da8cd49a0e048b6835c4a47_1440w.jpg)

- 点击“Customize”来取消勾选不需要的宏包。
  
 ![](https://pic4.zhimg.com/80/v2-e8d333584397c5bf2ff5ababbf0bfeef_1440w.jpg) 

 - 单是把非中英的语言包取消勾选可以省掉 1G 的空间，要是嫌麻烦全部安装也可以。安装界面右下角可选择是否安装 TeXworks 编辑器，我觉得既然都来看这篇文章了，那这个应该可以不要了。设置完安装路径等选项之后点击“安装”，之后静坐 20 分钟 - 3 小时等待安装完成。

$\Delta$ 安装 VSCode 上的 latex 插件

-  VSCode 安装完成之后，在扩展商店安装 LaTeX Workshop 插件。
  
$\Delta$ 配置 VSCode 上的 latex 插件

- 在 VSCode 界面下按下 F1，然后键入“setjson”，点击“首选项: 打开设置(JSON)”:
  ![](https://pic1.zhimg.com/80/v2-242cb974d60f44314a8a75b3f00366ec_1440w.jpg)

将下面的代码放入设置区：
```
"latex-workshop.latex.tools": [
    {
        // 编译工具和命令
        "name": "xelatex",
        "command": "xelatex",
        "args": [
            "-synctex=1",
            "-interaction=nonstopmode",
            "-file-line-error",
            "-pdf",
            "%DOCFILE%"
        ]
    },
    {
        "name": "pdflatex",
        "command": "pdflatex",
        "args": [
            "-synctex=1",
            "-interaction=nonstopmode",
            "-file-line-error",
            "%DOCFILE%"
        ]
    },
    {
        "name": "bibtex",
        "command": "bibtex",
        "args": [
            "%DOCFILE%"
        ]
    }
],
```
-  LaTeX Workshop 默认的编译工具是 latexmk，大家根据需要修改所需的工具和命令，我不需要用到 latexmk，因此我把其修改为中文环境常用的 xelatex，大家根据需要自行修改。（将 tools 中的 %DOC%替换成%DOCFILE%就可以支持编译中文路径下的文件了）
```
"latex-workshop.latex.recipes": [
    {
        "name": "xelatex",
        "tools": [
            "xelatex"
        ],
    },
    {
        "name": "pdflatex",
        "tools": [
            "pdflatex"
        ]
    },
    {
        "name": "xe->bib->xe->xe",
        "tools": [
            "xelatex",
            "bibtex",
            "xelatex",
            "xelatex"
        ]
    },
    {
        "name": "pdf->bib->pdf->pdf",
        "tools": [
            "pdflatex",
            "bibtex",
            "pdflatex",
            "pdflatex"
        ]
    }
],
```
$\Delta$ 用于配置编译链，同样地放入设置区。第一个 recipe 为默认的编译工具，如需要使用 bibtex 可使用如下方法：
 1. 在编译时单击 VSCode 界面左下角的小勾，单击“Build LaTeX project”，选择带 bib 的 Recipe，也可使用快捷键快速选择；
 2. 将带 bib 的 Recipe 放到第一位，就可以作为默认 Recipe 编译了，也可以但因为编译次数比较多，速度会比较慢；
 3. 在文档的开头添加 %!BIB program = bibtex

- 要使用 pdflatex，只需在 tex 文档首加入以下代码：
``
%!TEX program = pdflatex
``
- 要使用 SumatraPDF 预览编译好的PDF文件，添加以下代码进入设置区。
```
"latex-workshop.view.pdf.viewer": "external",

"latex-workshop.view.pdf.external.viewer.command": "C:/.../SumatraPDF.exe",
"latex-workshop.view.pdf.external.viewer.args": [
    "-forward-search",
    "%TEX%",
    "%LINE%",
    "-reuse-instance",
    "-inverse-search",
    "\"C:/.../Microsoft VS Code/Code.exe\" \"C:/.../Microsoft VS Code/resources/app/out/cli.js\" -gr \"%f\":\"%l\"",
    "%PDF%"
],
```
$\Delta$“viewer”选择使用外置阅读器，“viewer.command”和 “viewer.args”中有“...”的地方需要根据自己电脑上 SumatraPDF 和 VSCode 的安装位置进行修改，记得把盘符也改了。现在就可以使用 VSCode 编译 tex 文件并以 SumatraPDF 为阅读器预览了:

![](https://pic3.zhimg.com/80/v2-debe9b0aa5b43cc2a63183abcf2c6a2e_1440w.jpg)

$\Delta$插件经过几次更新之后已经去掉了右键菜单选项，选项被移动到了左侧栏。点击左侧栏的 [公式] 图标，再点击你所想要使用的Recipe 就可以编译了，如果用快捷键则默认使用第一条 Recipe 编译。单击右上角的放大镜按钮或按 Ctrl+Alt+v 打开 SumatraPDF 进行预览。

##  配置正向和反向搜索
```
"latex-workshop.view.pdf.external.synctex.command": "C:/.../SumatraPDF.exe",
"latex-workshop.view.pdf.external.synctex.args": [
    "-forward-search",
    "%TEX%",
    "%LINE%",
    "-reuse-instance",
    "-inverse-search",
    "\"C:/.../Microsoft VS Code/Code.exe\" \"C:/.../Microsoft VS Code/resources/app/out/cli.js\" -gr \"%f\":\"%l\"",
    "%PDF%",
],
```
$\Delta$ 添加代码进入设置区以配置正向搜索，和上面一样，里面“...”的部分结合自身情况修改（感谢 @Macrofuns指出，如果不加双引号，在文件路径有空格的情况下会导致无法反向搜索）。

![](https://pic1.zhimg.com/80/v2-dd2a34e6e12fb392b556d620ba814840_1440w.jpg)

$\Delta$单击“SyncTeX from cursor”即可正向搜索

![](https://pic1.zhimg.com/v2-ca18959ce71581a1814f9bcd7632bffc_b.webp)

$\Delta$可以看到，光标所在的行的内容在 PDF 中高亮显示（可以自己配置快捷键，我设置的是 Alt + S）。

![](https://pic1.zhimg.com/v2-9833aa8fe7b14bd6fac031eddfbc3608_b.jpg)
- 在PDF中双击即可反向搜索

- 不要清理生成的名字中带 synctex 的文件，否则就不能进行正向和反向搜索；之前的文章中，我提到了从 VSCode 预览按钮启SumatraPDF 会无法反向搜索的问题，现在已经解决，解决方法是在反向搜索命令中添加:
``"resources\app\out\cli.js"``
[Solution Source](https://link.zhihu.com/?target=https%3A//github.com/James-Yu/LaTeX-Workshop/issues/637%23issuecomment-473145503)

- 这个方法目前有个 bug，SumatraPDF 要从 VSCode 中打开才能进行反向搜索，单独打开的 SumatraPDF 在进行反向搜索时会跳转VSCode 的配置文件 cli.js。

- 如果编译出错，插件会弹出两个很烦人的气泡，不喜欢的话可以在设置中添加以下代码：
```
"latex-workshop.message.error.show": false,
"latex-workshop.message.warning.show": false,
```
### 附录
- 注意：只需把以下代码放入设置区的方括号里，不要删去方括号，不要忘记替换软件的路径。
```
// LaTeX
"latex-workshop.latex.autoBuild.run": "never",
"latex-workshop.message.error.show": false,
"latex-workshop.message.warning.show": false,

"latex-workshop.latex.tools": [
    {
        "name": "xelatex",
        "command": "xelatex",
        "args": [
            "-synctex=1",
            "-interaction=nonstopmode",
            "-file-line-error",
            "%DOCFILE%"
        ]
    },
    {
        "name": "pdflatex",
        "command": "pdflatex",
        "args": [
            "-synctex=1",
            "-interaction=nonstopmode",
            "-file-line-error",
            "%DOCFILE%"
        ]
    },
    {
        "name": "bibtex",
        "command": "bibtex",
        "args": [
            "%DOCFILE%"
        ]
    }
],

"latex-workshop.latex.recipes": [
    {
        "name": "xelatex",
        "tools": [
            "xelatex"
        ],
    },
    {
        "name": "pdflatex",
        "tools": [
            "pdflatex"
        ]
    },
    {
        "name": "xe->bib->xe->xe",
        "tools": [
            "xelatex",
            "bibtex",
            "xelatex",
            "xelatex"
        ]
    },
    {
        "name": "pdf->bib->pdf->pdf",
        "tools": [
            "pdflatex",
            "bibtex",
            "pdflatex",
            "pdflatex"
        ]
    }
],
"latex-workshop.view.pdf.viewer": "external",

"latex-workshop.view.pdf.external.viewer.command": "C:/.../SumatraPDF.exe",
"latex-workshop.view.pdf.external.viewer.args": [
    "-forward-search",
    "%TEX%",
    "%LINE%",
    "-reuse-instance",
    "-inverse-search",
    "\"C:/.../Microsoft VS Code/Code.exe\" \"C:/.../Microsoft VS Code/resources/app/out/cli.js\" -gr \"%f\":\"%l\"",
    "%PDF%"
],

"latex-workshop.view.pdf.external.synctex.command": "C:/.../SumatraPDF.exe",
"latex-workshop.view.pdf.external.synctex.args": [
    "-forward-search",
    "%TEX%",
    "%LINE%",
    "-reuse-instance",
    "-inverse-search",
    "\"C:/.../Microsoft VS Code/Code.exe\" \"C:/.../Microsoft VS Code/resources/app/out/cli.js\" -gr \"%f\":\"%l\"",
    "%PDF%",
],
```
