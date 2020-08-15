# Makefile --

PROGRAMS	= \
	conto-intesa--calcoli-esempio--etf-abcd						\
	conto-intesa--calcoli-esempio--etf-xyz						\
	\
	conto-intesa--calcoli-esempio--operazione-acquisto				\
	conto-intesa--calcoli-esempio--saldo-acquisto					\
	conto-intesa--calcoli-esempio--operazione-vendita				\
	conto-intesa--calcoli-esempio--rendimento-riepilogo				\
	conto-intesa--calcoli-esempio--strategie-prezzi--metodo-media-ponderata		\
	conto-intesa--calcoli-esempio--strategie-prezzi--metodo-linee-investimento

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

CLEANFILES	+= *.o

CC		= gcc -std=c11
CFLAGS		= -Wall
CPPFLAGS	= -I.
LDFLAGS		= -lm

## --------------------------------------------------------------------

conto-intesa--calcoli-esempio--etf-abcd:		\
		conto-intesa--calcoli-esempio--etf-abcd.c conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<

conto-intesa--calcoli-esempio--etf-xyz:		\
		conto-intesa--calcoli-esempio--etf-xyz.c conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<

## --------------------------------------------------------------------

conto-intesa--calcoli-esempio--operazione-acquisto:	\
		conto-intesa--calcoli-esempio--operazione-acquisto.c conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<

conto-intesa--calcoli-esempio--saldo-acquisto:		\
		conto-intesa--calcoli-esempio--saldo-acquisto.c conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<

conto-intesa--calcoli-esempio--operazione-vendita:	\
		conto-intesa--calcoli-esempio--operazione-vendita.c conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<

conto-intesa--calcoli-esempio--saldo-vendita:		\
		 conto-intesa--calcoli-esempio--saldo-vendita.c conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<

conto-intesa--calcoli-esempio--rendimento-riepilogo:		\
		 conto-intesa--calcoli-esempio--rendimento-riepilogo.c conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<

conto-intesa--calcoli-esempio--strategie-prezzi--metodo-media-ponderata:			\
		conto-intesa--calcoli-esempio--strategie-prezzi--metodo-media-ponderata.c	\
		conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<

conto-intesa--calcoli-esempio--strategie-prezzi--metodo-linee-investimento:		        \
		conto-intesa--calcoli-esempio--strategie-prezzi--metodo-linee-investimento.c	\
		conto-intesa--calcoli-esempio.h
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $<

## --------------------------------------------------------------------

CLEANFILES	+= demo

demo: demo.c
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $@ $< && ./demo


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

.PHONY: bootstrap clean-latex latex-clean

bootstrap:
	$(LATEX) conto-intesa-guida-etf.tex
	$(LATEX) conto-intesa-guida-etf.tex
	$(LATEX) conto-intesa-guida-etf.tex

clean-latex latex-clean:
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
