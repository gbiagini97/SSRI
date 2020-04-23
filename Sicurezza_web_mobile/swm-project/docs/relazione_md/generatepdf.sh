#!/bin/sh

pandoc --from=gfm relazione.md --dpi=250 -V fontsize=12pt -V geometry:margin=3cm --to=pdf -o relazione.pdf --pdf-engine=xelatex