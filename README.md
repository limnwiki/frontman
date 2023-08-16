# frontman - markdown frontmatter parser

I made this tool for use with [cmark](https://github.com/commonmark/cmark) on my [personal site](https://github.com/limnwiki/website) in conjunction with my static site generator [stags](https://github.com/limnwiki/stags)

# Usage
- `-i MARKDOWNFILE` selects input file
  
- `-g FIELD` prints frontmatter field
  - ex. `frontman -i test.md -g title`
    
- `-t MARKDOWNFILE FIELD TEMPLATEFILE TEMPLATEFIELD` replaces template field with frontmatter value
  - ex. `frontman -t test.md title template.html "\$title\$"` (replaces $ title $ in file)
    
- `-r VALUE TEMPLATEFILE TEMPLATEFIELD` replaces template field with input value
  - ex. `frontman -r "cool title" template.html "\$title\$"`
    
- `-v` removes frontmatter from markdown and prints it
  - useful when working with a markdown parser that can not parse frontmatter data (ex. cmark)
