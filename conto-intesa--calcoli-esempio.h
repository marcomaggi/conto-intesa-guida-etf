/* conto-intesa--calcoli-esempio.h -*- coding: utf-8-unix -*-

   Part of: Guida ETF Conto Intesa Sanpaolo
   Contents: libreria funzioni
   Date: Dec 27, 2017

   Abstract

	Libreria  di funzioni  per  i calcoli  di contabilità  per  le operazioni  di
	compravendita in ETF eseguite con i servizi di Banca Intesa Sanpaolo.

   Copyright (C) 2017, 2018, 2020 Marco Maggi <mrc.mgg@gmail.com>

   This program is free software: you can  redistribute it and/or modify it under the
   terms  of  the GNU  General  Public  License as  published  by  the Free  Software
   Foundation,  either version  3  of the  License,  or (at  your  option) any  later
   version.

   This program is  distributed in the hope  that it will be useful,  but WITHOUT ANY
   WARRANTY; without  even the implied warranty  of MERCHANTABILITY or FITNESS  FOR A
   PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   You should have received a copy of  the GNU General Public License along with this
   program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONTO_INTESA__CALCOLI_ESEMPIO_H
#define CONTO_INTESA__CALCOLI_ESEMPIO_H 1


/* ------------------------------------------------------------------ */
/* Headers.                                                           */
/* ------------------------------------------------------------------ */

#include <assert.h>
#include <locale.h>	/* per setlocale(LC_ALL, "it_IT") */
#include <math.h>	/* per nan("") e fabs() */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum tipo_operazione_t { ACQUISTO, VENDITA } tipo_operazione_t;


/** --------------------------------------------------------------------
 ** Helpers.
 ** ----------------------------------------------------------------- */

double
media_ponderata_2 (double peso_1, double valore_1, double peso_2, double valore_2)
{
  return (peso_1 * valore_1 + peso_2 * valore_2) / (peso_1 + peso_2);
}

double
media_ponderata_3 (double peso_1, double valore_1,
		   double peso_2, double valore_2,
		   double peso_3, double valore_3)
{
  return (peso_1 * valore_1 + peso_2 * valore_2 + peso_3 * valore_3) / (peso_1 + peso_2 + peso_3);
}

double
calcolo_rendimento_percentuale (double out, double in)
{
  return (100 * (out - in) / in);
}

bool
compare_double (double A, double B)
{
  return ((fabs(A - B) < 0.01)? true : false);
}

char const *
numero_ordine_parola (unsigned N)
{
  switch (N) {
  case 0:	return "zero";
  case 1:	return "uno";
  case 2:	return "due";
  case 3:	return "tre";
  case 4:	return "quattro";
  case 5:	return "cinque";
  case 6:	return "sei";
  case 7:	return "sette";
  case 8:	return "otto";
  case 9:	return "nove";
  case 10:	return "dieci";
  case 11:	return "undici";
  case 12:	return "dodici";
  default:	return "indefinito";
  }
}


/** --------------------------------------------------------------------
 ** Latex printing subroutines.
 ** ----------------------------------------------------------------- */

typedef struct latex_output_config_t	latex_output_config_t;

struct latex_output_config_t {
  FILE		* stream;
  char const	* ordine;
  char const	* prefisso;
  char const	* oggetto;
};

typedef latex_output_config_t const * const	latex_output_cfg_t;

/* ------------------------------------------------------------------ */

static void
print_latex_newcommand (FILE * stream, char const * const command_name, char const * const command_value)
{
  fprintf(stream, "\\newcommand{%s}{%s}\n", command_name, command_value);
}

static void
print_latex_newcommand_unsigned (latex_output_cfg_t config, char const * key, unsigned valore)
/* Stampa una  direttiva \newcommand il cui  valore è un  unsigned. */
{
  char	command_name[256];
  char	command_value[256];

  snprintf(command_name,  256, "\\%s%s%s%s", config->ordine, config->prefisso, config->oggetto, key);
  snprintf(command_value, 256, "%u", valore);
  print_latex_newcommand(config->stream, command_name, command_value);
}

static void
print_latex_newcommand_double_0 (latex_output_cfg_t config, char const * key, double valore)
/* Stampa una  direttiva \newcommand il cui  valore è un  double con 0 cifre  dopo la
   virgola. */
{
  char	command_name[256];
  char	command_value[256];

  snprintf(command_name,  256, "\\%s%s%s%s", config->ordine, config->prefisso, config->oggetto, key);
  snprintf(command_value, 256, "%.0f", valore);
  print_latex_newcommand(config->stream, command_name, command_value);
}

static void
print_latex_newcommand_double_2 (latex_output_cfg_t config, char const * key, double valore)
/* Stampa una  direttiva \newcommand il cui  valore è un  double con 2 cifre  dopo la
   virgola. */
{
  char	command_name[256];
  char	command_value[256];

  snprintf(command_name,  256, "\\%s%s%s%s", config->ordine, config->prefisso, config->oggetto, key);
  snprintf(command_value, 256, "%.2f", valore);
  print_latex_newcommand(config->stream, command_name, command_value);
}

static void
print_latex_newcommand_double_4 (latex_output_cfg_t config, char const * key, double valore)
/* Stampa una  direttiva \newcommand il cui  valore è un  double con 4 cifre  dopo la
   virgola. */
{
  char	command_name[256];
  char	command_value[256];

  snprintf(command_name,  256, "\\%s%s%s%s", config->ordine, config->prefisso, config->oggetto, key);
  snprintf(command_value, 256, "%.4f", valore);
  print_latex_newcommand(config->stream, command_name, command_value);
}

#undef  DEFINE_LATEX_PRINTER_UNSIGNED
#define DEFINE_LATEX_PRINTER_UNSIGNED(STEM, KEY)			\
  static void								\
  print_latex_ ## STEM (latex_output_cfg_t config, double STEM)		\
  {									\
    print_latex_newcommand_unsigned(config, KEY, STEM);			\
  }

#undef  DEFINE_LATEX_PRINTER_DOUBLE_0
#define DEFINE_LATEX_PRINTER_DOUBLE_0(STEM, KEY)			\
  static void								\
  print_latex_ ## STEM (latex_output_cfg_t config, double STEM)		\
  {									\
    print_latex_newcommand_double_0(config, KEY, STEM);			\
  }

#undef  DEFINE_LATEX_PRINTER_DOUBLE_2
#define DEFINE_LATEX_PRINTER_DOUBLE_2(STEM, KEY)			\
  static void								\
  print_latex_ ## STEM (latex_output_cfg_t config, double STEM)		\
  {									\
    print_latex_newcommand_double_2(config, KEY, STEM);			\
  }

#undef  DEFINE_LATEX_PRINTER_DOUBLE_4
#define DEFINE_LATEX_PRINTER_DOUBLE_4(STEM, KEY)		\
  static void							\
  print_latex_ ## STEM (latex_output_cfg_t config, double STEM)	\
  {								\
    print_latex_newcommand_double_4(config, KEY, STEM);		\
  }

/* ------------------------------------------------------------------ */

void
print_latex_newline (latex_output_cfg_t config)
{
  fprintf(config->stream, "\n");
}

void
print_latex_comment (latex_output_cfg_t config, char const * comment)
{
  fprintf(config->stream, "%% %s\n", comment);
}

/* ------------------------------------------------------------------ */

DEFINE_LATEX_PRINTER_UNSIGNED(numero_ordine,		"NumeroOrdine")
DEFINE_LATEX_PRINTER_DOUBLE_0(numero_quote,		"NumeroQuote")

DEFINE_LATEX_PRINTER_DOUBLE_2(prezzo_medio_effettivo,	"PrezzoMedioEffettivo")
DEFINE_LATEX_PRINTER_DOUBLE_2(prezzo_medio_eseguito,	"PrezzoMedioEffettivo")
DEFINE_LATEX_PRINTER_DOUBLE_4(prezzo_medio_carico,	"PrezzoMedioCarico")
DEFINE_LATEX_PRINTER_DOUBLE_4(costo_medio,		"CostoMedio")
DEFINE_LATEX_PRINTER_DOUBLE_2(costo_operazione,		"CostoOperazione")

DEFINE_LATEX_PRINTER_DOUBLE_2(controvalore_carico,	"ControvaloreCarico")
DEFINE_LATEX_PRINTER_DOUBLE_2(controvalore_operazione,	"ControvaloreOperazione")
DEFINE_LATEX_PRINTER_DOUBLE_2(controvalore_totale,	"ControvaloreTotale")

DEFINE_LATEX_PRINTER_DOUBLE_4(costo_acquisto_quote_vendute,	"CostoAcquistoQuoteVendute")

DEFINE_LATEX_PRINTER_DOUBLE_2(reddito_da_capitale,		"RedditoCapitale")
DEFINE_LATEX_PRINTER_DOUBLE_2(tassa_sul_reddito_da_capitale,	"TassaRedditoCapitale")

DEFINE_LATEX_PRINTER_DOUBLE_2(reddito_diverso_da_minusvalenza_sul_capitale,	"RedditoDiversoMinusvalenzaCapitale")
DEFINE_LATEX_PRINTER_DOUBLE_2(reddito_diverso_da_pagamento_commissioni,		"RedditoDiversoPagamentoCommissioni")
DEFINE_LATEX_PRINTER_DOUBLE_2(reddito_diverso_totale,				"RedditoDiversoTotale")
DEFINE_LATEX_PRINTER_DOUBLE_2(minusvalenza,					"Minusvalenza")

DEFINE_LATEX_PRINTER_DOUBLE_4(prezzo_medio_netto_vendita,	"PrezzoMedioNettoVendita")
DEFINE_LATEX_PRINTER_DOUBLE_4(utile_perdita_percentuale,	"UtilePerditaPercentuale")
DEFINE_LATEX_PRINTER_DOUBLE_4(utile_perdita_in_valuta,		"UtilePerditaInValuta")
DEFINE_LATEX_PRINTER_DOUBLE_4(rendimento_percentuale,		"RendimentoPercentuale")
DEFINE_LATEX_PRINTER_DOUBLE_4(rendimento_in_valuta,		"RendimentoInValuta")


/** --------------------------------------------------------------------
 ** Definizione tipo: saldo dopo un'operazione di compravendita.
 ** ----------------------------------------------------------------- */

typedef struct saldo_t		saldo_t;

struct saldo_t {
  /* Numero d'ordine dell'operazione precedente a questo saldo. */
  unsigned	numero_ordine;

  /* Totale del numero quote in carico. */
  double	numero_quote;

  /* Media  ponderata dei  prezzi medi  con  cui gli  ordini di  acquisto sono  stati
     eseguiti sulla Borsa di negoziazione. */
  double	prezzo_medio_effettivo;

  /* Media ponderata dei prezzi medi di carico delle quote acquistate. */
  double	prezzo_medio_carico;

  /* Costo medio di acquisto delle quote in carico. */
  double	costo_medio_quote;

  /* Prodotto tra il numero di quote in carico e il prezzo medio di carico. */
  double	controvalore_carico;

  /* Le  minusvalenze accumulate,  dovute ai  costi di  compravendita e  alle perdite
     classificate come redditi diversi.  È un numero negativo. */
  double	minusvalenze_accumulate;
};

saldo_t const saldo_precedente_convenzionale = {
  .numero_ordine		= 0,
  .numero_quote			= 0.0,
  .prezzo_medio_effettivo	= 0.0,
  .prezzo_medio_carico		= 0.0,
  .costo_medio_quote		= 0.0,
  .controvalore_carico		= 0.0,
  .minusvalenze_accumulate	= 0.0,
};

void
saldo_print_ascii (FILE * stream, saldo_t const * const S)
{
  fprintf(stream, "-- Saldo %u\n\n", S->numero_ordine);
  fprintf(stream, "%-50s= %10u\n",		"numero d'ordine",		S->numero_ordine);
  fprintf(stream, "%-50s= %10.0f\n",		"numero quote",			S->numero_quote);
  fprintf(stream, "%-50s= %12.4f EUR\n",	"prezzo medio effettivo",	S->prezzo_medio_effettivo);
  fprintf(stream, "%-50s= %12.4f EUR\n",	"prezzo medio carico",		S->prezzo_medio_carico);
  fprintf(stream, "%-50s= %12.4f EUR\n",	"costo medio per quota",	S->costo_medio_quote);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"controvalore di carico",	S->controvalore_carico);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"minusvalenze accumulate",	S->minusvalenze_accumulate);
  fprintf(stream, "\n");
}

void
saldo_print_latex (FILE * stream, char const * prefisso, saldo_t const * const S)
{
  latex_output_config_t		config = {
    .stream	= stream,
    .ordine	= numero_ordine_parola(S->numero_ordine),
    .prefisso	= prefisso,
    .oggetto	= "Saldo",
  };

  print_latex_comment			(&config, "Saldo contabile");
  print_latex_numero_ordine		(&config, S->numero_ordine);
  print_latex_numero_quote		(&config, S->numero_quote);
  print_latex_prezzo_medio_effettivo	(&config, S->prezzo_medio_effettivo);
  print_latex_prezzo_medio_carico	(&config, S->prezzo_medio_carico);
  print_latex_costo_medio		(&config, S->costo_medio_quote);
  print_latex_controvalore_carico	(&config, S->controvalore_carico);
  print_latex_minusvalenza		(&config, S->minusvalenze_accumulate);
  print_latex_newline			(&config);
}


/** --------------------------------------------------------------------
 ** Type definitions: operazione acquisto.
 ** ----------------------------------------------------------------- */

typedef struct operazione_acquisto_t	operazione_acquisto_t;

struct operazione_acquisto_t {
  /* Numero d'ordine dell'operazione. */
  unsigned		numero_ordine;

  tipo_operazione_t	tipo;

  /* Numero di quote acquistate in questa operazione. */
  double		numero_quote;

  /* Prezzo medio dell'ordine di acquisto eseguito sulla Borsa di negoziazione. */
  double		prezzo_medio_eseguito;

  /* Prodotto tra numero quote e prezzo medio eseguito. */
  double		controvalore_operazione;

  /* Costo dell'operazione di acquisto. */
  double		costo_operazione_acquisto;

  /* Controvalore totale dell'operazione di acquisto: è la somma addebitata sul Conto
     Corrente. */
  double		controvalore_totale;

  /* Prezzo medio di carico di ogni quota acquistata. */
  double		prezzo_medio_carico;
};

void
operazione_acquisto_init (operazione_acquisto_t * const O)
/* I seguenti  campi della  struttura O  devono essere  inizializzati: numero_ordine,
   numero_quote, prezzo_medio_eseguito. */
{
  assert(O->numero_ordine > 0);
  assert(O->numero_quote > 0);
  assert(O->prezzo_medio_eseguito > 0.0);
  O->tipo			= ACQUISTO;
  O->controvalore_operazione	= O->numero_quote * O->prezzo_medio_eseguito;
  O->costo_operazione_acquisto	= 0.50 + 2.50 + 0.0024 * O->controvalore_operazione;
  O->controvalore_totale	= O->controvalore_operazione + O->costo_operazione_acquisto;
  O->prezzo_medio_carico	= O->controvalore_totale / O->numero_quote;
}

void
operazione_acquisto_print_ascii (FILE * stream, operazione_acquisto_t const * const O)
{
  fprintf(stream, "-- Operazione %u: acquisto\n\n", O->numero_ordine);
  fprintf(stream, "%-50s= %10u\n",		"numero d'ordine",		O->numero_ordine);
  fprintf(stream, "%-50s= %10.0f\n",		"numero quote",			O->numero_quote);
  fprintf(stream, "%-50s= %12.4f EUR\n",	"prezzo medio eseguito",	O->prezzo_medio_eseguito);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"controvalore dell'operazione",	O->controvalore_operazione);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"costo dell'operazione",	O->costo_operazione_acquisto);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"controvalore totale",		O->controvalore_totale);
  fprintf(stream, "%-50s= %12.4f EUR\n",	"prezzo medio di carico",	O->prezzo_medio_carico);
  fprintf(stream, "\n");
}

void
operazione_acquisto_print_latex (FILE * stream, char const * prefisso, operazione_acquisto_t const * const O)
{
  latex_output_config_t		config = {
    .stream	= stream,
    .ordine	= numero_ordine_parola(O->numero_ordine),
    .prefisso	= prefisso,
    .oggetto	= "Acquisto",
  };

  print_latex_comment			(&config, "Operazione di acquisto");
  print_latex_numero_ordine		(&config, O->numero_ordine);
  print_latex_numero_quote		(&config, O->numero_quote);
  print_latex_prezzo_medio_eseguito	(&config, O->prezzo_medio_eseguito);
  print_latex_controvalore_operazione	(&config, O->controvalore_operazione);
  print_latex_costo_operazione		(&config, O->costo_operazione_acquisto);
  print_latex_controvalore_totale	(&config, O->controvalore_totale);
  print_latex_prezzo_medio_carico	(&config, O->prezzo_medio_carico);
  print_latex_newline			(&config);
}

void
saldo_acquisto_init (saldo_t * const S, operazione_acquisto_t const * const O, saldo_t const * const S_precedente)
/* Aggiorna una struttura "saldo_t" dopo un'operazione di acquisto. */
{
  S->numero_ordine		= O->numero_ordine;
  S->numero_quote		= O->numero_quote + S_precedente->numero_quote;
  S->prezzo_medio_effettivo	= media_ponderata_2(O->numero_quote, O->prezzo_medio_eseguito,
						    S_precedente->numero_quote, S_precedente->prezzo_medio_effettivo);
  S->prezzo_medio_carico	= media_ponderata_2(O->numero_quote, O->prezzo_medio_carico,
						    S_precedente->numero_quote, S_precedente->prezzo_medio_carico);
  S->costo_medio_quote		= S->prezzo_medio_carico - S->prezzo_medio_effettivo;
  S->controvalore_carico	= S->numero_quote * S->prezzo_medio_carico;
  S->minusvalenze_accumulate	= S_precedente->minusvalenze_accumulate;
}


/** --------------------------------------------------------------------
 ** Type definitions: operazione vendita.
 ** ----------------------------------------------------------------- */

typedef struct operazione_vendita_t	operazione_vendita_t;

struct operazione_vendita_t {
  /* Numero d'ordine dell'operazione. */
  unsigned		numero_ordine;

  tipo_operazione_t	tipo;

  /* Numero di quote vendute in questa operazione. */
  double		numero_quote;

  /* Prezzo medio dell'ordine di vendita eseguito sulla Borsa di negoziazione. */
  double		prezzo_medio_eseguito;

  /* Prodotto tra numero quote e prezzo medio effettivo. */
  double		controvalore_operazione;

  /* Reddito  da  capitale  dell'operazione  di vendita,  rispetto  al  prezzo  medio
     effettivo di acquisto nel saldo. */
  double		reddito_da_capitale;

  /* Reddito diverso  dovuto a una  minusvalenza sul  capitale dopo la  vendita delle
     quote;  è un  numero negativo.   Se la  vendita genera  una plusvalenza:  questo
     valore è zero. */
  double		reddito_diverso_minusvalenza_capitale;

  /* Reddito diverso  dovuto al  pagamento di  commissioni di  compravendita.  Questo
     valore è sempre strettamente negativo. */
  double		reddito_diverso_pagamento_commissioni;

  /* Reddito diverso totale dovuto alla vendita di quote.  È un numero negativo somma
     tra il reddito diverso da minusvalenza  sul capitale e il reddito diverso dovuto
     al pagamento delle commissioni. */
  double		reddito_diverso_totale;

  /* Tassa sul reddito da capitale. */
  double		tassa_sul_reddito_da_capitale;

  /* Costo di  acquisto delle quote vendute:  prodotto tra numero di  quote vendute e
     costo medio di una quota in carico nel saldo. */
  double		costo_acquisto_quote_vendute;

  /* Costo dell'operazione di vendita. */
  double		costo_operazione_vendita;

  /* Controvalore   totale   dell'operazione:    differenza   tra   il   controvalore
     dell'operazione e la somma tra costo e  tassa.  È la somma accreditata sul Conto
     Corrente. */
  double		controvalore_totale;

  /* Prezzo medio  netto di  vendita: rapporto  tra controvalore  totale e  numero di
     quote vendute. */
  double		prezzo_medio_netto;

  /* Rendimento percentuale di questa vendita al lordo di costi e tasse.  È il valore
     che  sarebbe   mostrato  nella  tabella   del  patrimonio  sul  sito   di  banca
     telematica. */
  double		utile_perdita_percentuale;

  /* Rendimento in valuta di  questa vendita al lordo di costi e  tasse.  È il valore
     che  sarebbe   mostrato  nella  tabella   del  patrimonio  sul  sito   di  banca
     telematica. */
  double		utile_perdita_in_valuta;

  /* Rendimento percentuale di questa vendita rispetto  al prezzo medio di carico nel
     saldo. */
  double		rendimento_percentuale;

  /* Rendimento in  valuta di questa vendita  rispetto al prezzo medio  di carico nel
     saldo. */
  double		rendimento_in_valuta;
};

void
operazione_vendita_init (operazione_vendita_t * const O, saldo_t const * const S_precedente)
/* I seguenti  campi della  struttura O  devono essere  inizializzati: numero_ordine,
   numero_quote, prezzo_medio_eseguito. */
{
  double	reddito_vendita;

  assert(O->numero_ordine > 0);
  assert(O->numero_quote > 0);
  assert(O->prezzo_medio_eseguito > 0.0);
  O->tipo				= VENDITA;
  O->controvalore_operazione		= O->numero_quote * O->prezzo_medio_eseguito;
  reddito_vendita			= O->numero_quote * (O->prezzo_medio_eseguito - S_precedente->prezzo_medio_effettivo);
  if (reddito_vendita > 0.0) {
    O->reddito_da_capitale		= reddito_vendita;
    O->tassa_sul_reddito_da_capitale	= (O->reddito_da_capitale > 0.0)? (0.26 * O->reddito_da_capitale) : 0.0;
  } else {
    O->reddito_da_capitale		= 0.0;
    O->tassa_sul_reddito_da_capitale	= 0.0;
  }
  O->costo_acquisto_quote_vendute	= O->numero_quote * (S_precedente->prezzo_medio_carico - S_precedente->prezzo_medio_effettivo);
  O->costo_operazione_vendita		= 0.50 + 2.50 + 0.0024 * O->controvalore_operazione;
  O->controvalore_totale		= O->controvalore_operazione - (O->costo_operazione_vendita + O->tassa_sul_reddito_da_capitale);
  O->prezzo_medio_netto			= O->controvalore_totale / O->numero_quote;

  O->utile_perdita_percentuale		= calcolo_rendimento_percentuale(O->prezzo_medio_eseguito, S_precedente->prezzo_medio_carico);
  O->utile_perdita_in_valuta		= O->numero_quote * (O->prezzo_medio_eseguito - S_precedente->prezzo_medio_carico);

  O->rendimento_percentuale		= calcolo_rendimento_percentuale(O->prezzo_medio_netto, S_precedente->prezzo_medio_carico);
  O->rendimento_in_valuta		= O->numero_quote * (O->prezzo_medio_netto - S_precedente->prezzo_medio_carico);

  O->reddito_diverso_minusvalenza_capitale = ((reddito_vendita > 0.0)? 0.0 : reddito_vendita);
  O->reddito_diverso_pagamento_commissioni = (reddito_vendita - (O->costo_acquisto_quote_vendute + O->costo_operazione_vendita)) - reddito_vendita;
  O->reddito_diverso_totale		= O->reddito_diverso_pagamento_commissioni + O->reddito_diverso_minusvalenza_capitale;
}

void
operazione_vendita_print_ascii (FILE * stream, operazione_vendita_t const * const O)
{
  fprintf(stream, "-- Operazione %u: vendita\n\n", O->numero_ordine);
  fprintf(stream, "%-50s= %10u\n",		"numero d'ordine",			O->numero_ordine);
  fprintf(stream, "%-50s= %10.0f\n",		"numero quote",				O->numero_quote);
  fprintf(stream, "%-50s= %12.4f EUR\n",	"prezzo medio eseguito",		O->prezzo_medio_eseguito);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"controvalore dell'operazione",		O->controvalore_operazione);
  fprintf(stream, "\n");
  fprintf(stream, "%-50s= %10.2f EUR\n",	"reddito da capitale",			O->reddito_da_capitale);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"tassa sul reddito da capitale",	O->tassa_sul_reddito_da_capitale);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"costo dell'operazione di vendita",	O->costo_operazione_vendita);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"costo di acquisto quote vendute",	O->costo_acquisto_quote_vendute);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"reddito diverso da minusvalenza sul capitale", O->reddito_diverso_minusvalenza_capitale);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"reddito diverso da pagamento commissioni", O->reddito_diverso_pagamento_commissioni);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"reddito diverso totale",		O->reddito_diverso_totale);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"minusvalenza",				-(O->reddito_diverso_totale));
  fprintf(stream, "\n");
  fprintf(stream, "%-50s= %10.2f EUR\n",	"controvalore totale",			O->controvalore_totale);
  fprintf(stream, "%-50s= %12.4f EUR\n",	"prezzo medio netto",			O->prezzo_medio_netto);
  fprintf(stream, "%-50s= %12.4f%%\n",		"Utile/Perdita percentuale",		O->utile_perdita_percentuale);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"Utile/Perdita in valuta",		O->utile_perdita_in_valuta);
  fprintf(stream, "%-50s= %12.4f%%\n",		"rendimento percentuale",		O->rendimento_percentuale);
  fprintf(stream, "%-50s= %10.2f EUR\n",	"rendimento in valuta",			O->rendimento_in_valuta);
  fprintf(stream, "\n");
}

void
operazione_vendita_print_latex (FILE * stream, char const * prefisso, operazione_vendita_t const * const O)
{
  latex_output_config_t		config = {
    .stream	= stream,
    .ordine	= numero_ordine_parola(O->numero_ordine),
    .prefisso	= prefisso,
    .oggetto	= "Vendita",
  };

  print_latex_comment				(&config, "Operazione di vendita");
  print_latex_numero_ordine			(&config, O->numero_ordine);
  print_latex_numero_quote			(&config, O->numero_quote);
  print_latex_prezzo_medio_eseguito		(&config, O->prezzo_medio_eseguito);
  print_latex_controvalore_operazione		(&config, O->controvalore_operazione);
  print_latex_costo_operazione			(&config, O->costo_operazione_vendita);
  print_latex_costo_acquisto_quote_vendute	(&config, O->costo_acquisto_quote_vendute);
  print_latex_controvalore_totale		(&config, O->controvalore_totale);

  print_latex_reddito_da_capitale		(&config, O->reddito_da_capitale);
  print_latex_tassa_sul_reddito_da_capitale	(&config, O->tassa_sul_reddito_da_capitale);

  print_latex_reddito_diverso_da_minusvalenza_sul_capitale	(&config, O->reddito_diverso_minusvalenza_capitale);
  print_latex_reddito_diverso_da_pagamento_commissioni		(&config, O->reddito_diverso_pagamento_commissioni);
  print_latex_reddito_diverso_totale				(&config, O->reddito_diverso_totale);
  print_latex_minusvalenza					(&config, -(O->reddito_diverso_totale));

  print_latex_prezzo_medio_netto_vendita	(&config, O->prezzo_medio_netto);
  print_latex_utile_perdita_percentuale		(&config, O->utile_perdita_percentuale);
  print_latex_utile_perdita_in_valuta		(&config, O->utile_perdita_in_valuta);
  print_latex_rendimento_percentuale		(&config, O->rendimento_percentuale);
  print_latex_rendimento_in_valuta		(&config, O->rendimento_in_valuta);

  print_latex_newline				(&config);
}

void
saldo_vendita_init (saldo_t * const S, operazione_vendita_t const * const O, saldo_t const * const S_precedente)
/* Aggiorna una struttura "saldo_t" dopo un'operazione di vendita. */
{
  S->numero_ordine		= O->numero_ordine;
  S->numero_quote		= S_precedente->numero_quote - O->numero_quote;
  if (S->numero_quote > 0) {
    S->prezzo_medio_effettivo	= S_precedente->prezzo_medio_effettivo;
    S->prezzo_medio_carico	= S_precedente->prezzo_medio_carico;
    S->costo_medio_quote	= S_precedente->costo_medio_quote;
    S->controvalore_carico	= S->numero_quote * S->prezzo_medio_carico;
  } else {
    S->prezzo_medio_effettivo	= 0.0;
    S->prezzo_medio_carico	= 0.0;
    S->costo_medio_quote	= 0.0;
    S->controvalore_carico	= 0.0;
  }
  S->minusvalenze_accumulate	= S_precedente->minusvalenze_accumulate - O->reddito_diverso_totale;
}


/** --------------------------------------------------------------------
 ** Type definitions: operazione.
 ** ----------------------------------------------------------------- */

typedef union operazione_t	operazione_t;

union operazione_t {
  operazione_acquisto_t		acquisto;
  operazione_vendita_t		vendita;
  struct {
    unsigned		numero_ordine;
    tipo_operazione_t	tipo;
    double		numero_quote;
    double		prezzo_medio_eseguito;
  };
};

void
operazione_init (operazione_t * const O, saldo_t const * const S_precedente)
/* I  seguenti   campi  della   struttura  O   devono  essere   inizializzati:  tipo,
   numero_quote, prezzo_medio_eseguito. */
{
  if (ACQUISTO == O->tipo) {
    operazione_acquisto_init (&(O->acquisto));
  } else {
    operazione_vendita_init  (&(O->vendita), S_precedente);
  }
}

void
operazione_print_ascii (FILE * stream, operazione_t const * const O)
{
  if (ACQUISTO == O->tipo) {
    operazione_acquisto_print_ascii(stream, &(O->acquisto));
  } else {
    operazione_vendita_print_ascii (stream, &(O->vendita));
  }
}

void
operazione_print_latex (FILE * stream, char const * prefisso, operazione_t const * const O)
{
  if (ACQUISTO == O->tipo) {
    operazione_acquisto_print_latex(stream, prefisso, &(O->acquisto));
  } else {
    operazione_vendita_print_latex (stream, prefisso, &(O->vendita));
  }
}

void
saldo_init (saldo_t * const S, operazione_t const * const O, saldo_t const * const S_precedente)
/* I  seguenti   campi  della   struttura  O   devono  essere   inizializzati:  tipo,
   numero_quote, prezzo_medio_eseguito. */
{
  if (ACQUISTO == O->tipo) {
    saldo_acquisto_init (S, &(O->acquisto), S_precedente);
  } else {
    saldo_vendita_init  (S, &(O->vendita),  S_precedente);
  }
}


/** --------------------------------------------------------------------
 ** Calcolo storico.
 ** ----------------------------------------------------------------- */

void
operazione_e_saldo (operazione_t * O, saldo_t * S, saldo_t const * const S_precedente)
{
  operazione_init(O, S_precedente);
  saldo_init(S, O, S_precedente);
}

void
calcolo_storico (unsigned numero_operazioni, operazione_t * O, saldo_t * S)
{
  operazione_e_saldo(&O[0], &S[0], &saldo_precedente_convenzionale);
  for (unsigned i=1; i<numero_operazioni; ++i) {
    operazione_e_saldo(&O[i], &S[i], &S[i-1]);
  }
}

void
calcolo_storico_print_ascii (FILE * stream, unsigned numero_operazioni, operazione_t * O, saldo_t * S)
{
  saldo_print_ascii(stream, &saldo_precedente_convenzionale);
  for (unsigned i=0; i<numero_operazioni; ++i) {
    operazione_print_ascii(stream, &O[i]);
    saldo_print_ascii(stream, &S[i]);
  }
  fprintf(stream, "\n");
  fflush(stream);
}

void
calcolo_storico_print_latex (FILE * stream, char const * prefisso, unsigned numero_operazioni, operazione_t * O, saldo_t * S)
{
  saldo_print_latex(stream, prefisso, &saldo_precedente_convenzionale);
  for (unsigned i=0; i<numero_operazioni; ++i) {
    operazione_print_latex(stream, prefisso, &O[i]);
    saldo_print_latex(stream, prefisso, &S[i]);
  }
  fprintf(stream, "\n");
  fflush(stream);
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* CONTO_INTESA__CALCOLI_ESEMPIO_H */

/* end of file */
