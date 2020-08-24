# Makefile --

PROGRAMS	= \
	conto-intesa--calcoli-esempio--etf-abcd.exe					\
	conto-intesa--calcoli-esempio--etf-xyz.exe					\
	\
	conto-intesa--calcoli-esempio--operazione-acquisto.exe				\
	conto-intesa--calcoli-esempio--saldo-acquisto.exe				\
	conto-intesa--calcoli-esempio--operazione-vendita.exe				\
	conto-intesa--calcoli-esempio--rendimento-riepilogo.exe				\
	conto-intesa--calcoli-esempio--strategie-prezzi--metodo-media-ponderata.exe	\
	conto-intesa--calcoli-esempio--strategie-prezzi--metodo-linee-investimento.exe	\
	conto-intesa--calcoli-esempio--verifica-prezzo-pareggio.exe

DOCUMENTS	= \
	conto-intesa-guida-etf.pdf

CLEANFILES	= $(DOCUMENTS) $(PROGRAMS)

RM		= /bin/rm --verbose --force --recursive

## --------------------------------------------------------------------

.PHONY: all clean

all: $(PROGRAMS) $(DOCUMENTS)

clean: clean-latex
	$(RM) $(CLEANFILES)


#### programmi per calcoli negli esempi della guida

CLEANFILES	+= *.o *.inc

CC		= gcc -std=c11
CFLAGS		= -Wall
CPPFLAGS	= -I.
LDFLAGS		= -lm

%.exe: %.c conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<


#### documenti

MY_INC_FILES	= \
	conto-intesa--calcoli-esempio--operazione-acquisto.inc				\
	conto-intesa--calcoli-esempio--saldo-acquisto.inc				\
	conto-intesa--calcoli-esempio--operazione-vendita.inc				\
	conto-intesa--calcoli-esempio--strategie-prezzi--metodo-media-ponderata.inc	\
	conto-intesa--calcoli-esempio--strategie-prezzi--metodo-linee-investimento.inc

PREREQUISITES	= $(MY_INC_FILES)

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

.PHONY: bootstrap clean-latex latex-clean incs

bootstrap: $(PREREQUISITES)
	$(LATEX) conto-intesa-guida-etf.tex
	$(LATEX) conto-intesa-guida-etf.tex
	$(LATEX) conto-intesa-guida-etf.tex

clean-latex latex-clean:
	if test -d "=auto" ; then /bin/chmod 0750 "=auto" ; fi

## --------------------------------------------------------------------

conto-intesa-guida-etf.dvi: conto-intesa-guida-etf.tex fdl-1.3.tex $(PREREQUISITES)

## --------------------------------------------------------------------

incs: $(MY_INC_FILES)

%.inc: %.exe
	./$(^) latex >$(@)

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
