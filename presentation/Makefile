TEX = pdflatex
ARGS = -halt-on-error

NAME = presentation
TARGET = $(NAME).pdf
DEPS = presentation.tex

RERUN = "(There were undefined references|Rerun to get (cross-references|the bars|outlines))"

.PHONY: all clean

all: $(TARGET)

view: $(TARGET)
	xpdf $<

$(TARGET): $(NAME).tex $(DEPS)
	$(TEX) -jobname=$(NAME) $(ARGS) $<
	@egrep -q $(RERUN) $(NAME).log && ($(TEX) -jobname=$(NAME) $(ARGS) $<); true

clean:
	@rm -f $(NAME).out $(NAME).aux $(NAME).log $(NAME).toc $(NAME).nav $(NAME).snm $(NAME).vrb $(NAME).pdf
