Clang Format (Demo)
===================

clang-format is a command-line-tool written in
c++ based on llvm/clang's libformat!

Usage
-----

Just call the beast:)

::

    clang-format file > out_file

Editors
.......

Or use it from within an editor/IDE:

- M$ VisualStudio >= 2010
- vim
- sublime text

Options / Options-File
......................

Clang format will use options given on the commandline
given like::

    clang-format -style=<style> <file>
    clang-format -style="{BasedOnStyle: <style>, option: <value>}" <file>

Alternatively it can read it's configuration from a file
in the *root* of your project the file has to be named
`.clang-format` or `_clang-format`.

Create Options File::

    clang-format -style=llvm -dump-config > .clang-format

SCMs
....

You can use `clang-format-diff` as step in commiting (e.g. git/hook).
But you might loose info for blame especially if your scm handles
whitespace changes poorly.

Links
-----

- http://clang.llvm.org/docs/ClangFormat.html
- http://clang.llvm.org/docs/ClangFormatStyleOptions.html
- http://llvm.org/builds/ (vs plugin)

Other Hot Tools
---------------

- clang completion (vim, xcode, ...)
- templar/templight (template debugging)
- modernize
- ...
