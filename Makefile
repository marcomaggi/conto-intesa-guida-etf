# Makefile --

PROGRAMS	= \
	conto-intesa-etf-esempio-1

DOCUMENTS	= \
	conto-intesa-guida-etf.pdf

CLEANFILES	= $(DOCUMENTS) $(PROGRAMS)

RM		= /bin/rm --verbose --force --recursive

## --------------------------------------------------------------------

.PHONY: all clean bootstrap-latex clean-latex

all: $(PROGRAMS) $(DOCUMENTS)

clean: clean-latex
	$(RM) $(CLEANFILES)

#page
#### programmi

CLEANFILES	+= *.o

CC		= gcc -std=c11
CFLAGS		= -Wall
CPPFLAGS	= -I.

## --------------------------------------------------------------------

conto-intesa-etf.o: conto-intesa-etf.c conto-intesa-etf.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

conto-intesa-etf-esempio-1.o: conto-intesa-etf-esempio-1.c conto-intesa-etf.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

conto-intesa-etf-esempio-1: conto-intesa-etf-esempio-1.o conto-intesa-etf.o
	$(CC) $(CFLAGS) -o $@ $^

#page
#### documenti

CLEANFILES	+= \
	*.aux *.log *.toc *.dvi *.ps* *.pdf *.eps *.bbl *.blg \
	*.idx *.out *.texdraw _region_.tex "=auto"

.SECONDARY: %.dvi .%.ps

LATEX		= latex
PS2PDF		= ps2pdf
DVIPS		= dvips

PDFLATEX	= pdflatex

PAPER		?= a4
ifeq ($(PAPER),a5)
DVIPSFLAGS	:= -T 420pt,595pt
endif

## --------------------------------------------------------------------

bootstrap-latex:
	$(LATEX) conto-intesa-guida-etf.tex
	$(LATEX) conto-intesa-guida-etf.tex
	$(LATEX) conto-intesa-guida-etf.tex

clean-latex:
	if test -d "=auto" ; then /bin/chmod 0750 "=auto" ; fi

## --------------------------------------------------------------------

conto-intesa-guida-etf.dvi: conto-intesa-guida-etf.tex fdl-1.3.tex

## --------------------------------------------------------------------

ifeq (1,1)

%.dvi: %.tex
	$(LATEX) $(<)

%.ps: %.dvi
	$(DVIPS) $(DVIPSFLAGS) -o $(@) $(<)

%.pdf: %.ps
	$(PS2PDF) $(<) $(@)

else

%.pdf: %.tex
	$(LATEX) $(<) && $(PDFLATEX) $(<)

endif

### end of file
