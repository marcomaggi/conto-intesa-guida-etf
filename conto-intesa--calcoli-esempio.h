/* conto-intesa--calcoli-esempio--saldo-acquisto.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di  esempio nella  guida, per la  sezione "Aggiornamento
	del saldo dopo un'operazione di acquisto".

   Copyright (C) 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

   This program is free software:  you can redistribute it and/or modify
   it under the terms of the  GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or (at
   your option) any later version.

   This program is  distributed in the hope that it  will be useful, but
   WITHOUT  ANY   WARRANTY;  without   even  the  implied   warranty  of
   MERCHANTABILITY or  FITNESS FOR  A PARTICULAR  PURPOSE.  See  the GNU
   General Public License for more details.

   You should  have received a  copy of  the GNU General  Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
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


/** --------------------------------------------------------------------
 ** Type definitions: saldo dopo compravendita.
 ** ----------------------------------------------------------------- */

typedef struct saldo_t		saldo_t;

struct saldo_t {
  /* Numero d'ordine dell'operazione precedente a questo saldo. */
  unsigned	numero_ordine;

  /* Data  dell'ultima   operazione  prima  del  saldo.    È  usata  per
     arricchire  la descrizione.   Questo campo  può essere  impostata a
     NULL se non si vuole specificare una data. */
  char const *	data_operazione;

  /* Totale del numero quote in carico. */
  double	numero_quote;

  /* Media  ponderata  dei  prezzi  medi effettivi  di  acquisto:  media
     ponderata dei prezzi  medi degli ordini di  acquisto eseguiti sulla
     Borsa  di   negoziazione.   In  generale,  questo   valore  dipende
     dall'ordine in cui gli acquisti  sono eseguiti e intercalati con le
     vendite. */
  double	prezzo_medio_effettivo;

  /* Media  ponderata  dei  prezzi  medi  di  carico  di  acquisto.   In
     generale,  questo valore  dipende dall'ordine  in cui  gli acquisti
     sono eseguiti e intercalati con le vendite. */
  double	prezzo_medio_carico;

  /* Costo medio per quota degli acquisti effettuati finora. */
  double	costo_medio_acquisti;

  /* Prodotto tra  il numero  di quote  in carico e  il prezzo  medio di
     carico. */
  double	controvalore_carico;

  /* Le minusvalenze accumulate, dovute ai costi di compravendita.  È un
     numero negativo. */
  double	minusvalenze_accumulate;
};

saldo_t const saldo_precedente_convenzionale = {
  .numero_ordine		= 0,
  .data_operazione		= "2000 dicembre 31",
  .numero_quote			= 0.0,
  .prezzo_medio_effettivo	= 0.0,
  .costo_medio_acquisti		= 0.0,
  .prezzo_medio_carico		= 0.0,
  .controvalore_carico		= 0.0,
  .minusvalenze_accumulate	= 0.0,
};

#define saldo_convenzionale_precedente	saldo_precedente_convenzionale

void
saldo_print_ascii (FILE * stream, saldo_t const * const S)
{
  fprintf(stream, "-- Saldo %u (%s)\n\n", S->numero_ordine,
	  ((S->data_operazione)? S->data_operazione : "nessuna data"));
  fprintf(stream, "%-40s= %10u\n",	"numero d'ordine",		S->numero_ordine);
  fprintf(stream, "%-40s= %10.0f\n",	"numero quote",			S->numero_quote);
  fprintf(stream, "%-40s= %10.2f EUR\n", "prezzo medio effettivo",	S->prezzo_medio_effettivo);
  fprintf(stream, "%-40s= %12.4f EUR\n", "costo medio per quota",	S->costo_medio_acquisti);
  fprintf(stream, "%-40s= %12.4f EUR\n", "prezzo medio carico",		S->prezzo_medio_carico);
  fprintf(stream, "%-40s= %10.2f EUR\n", "controvalore di carico",	S->controvalore_carico);
  fprintf(stream, "%-40s= %10.2f EUR\n", "minusvalenze accumulate",	S->minusvalenze_accumulate);
  fprintf(stream, "\n");
}


/** --------------------------------------------------------------------
 ** Type definitions: operazione acquisto.
 ** ----------------------------------------------------------------- */

typedef struct operazione_acquisto_t	operazione_acquisto_t;

struct operazione_acquisto_t {
  /* Numero d'ordine dell'operazione. */
  unsigned		numero_ordine;

  tipo_operazione_t	tipo;

  /* Data  dell'operazione  di  acquisto.   È usata  per  arricchire  la
     descrizione.  Questo  campo può essere  impostata a NULL se  non si
     vuole specificare una data. */
  char const *		data_operazione;

  /* Totale del numero quote in carico. */
  double		numero_quote;

  /* Prezzo medio  dell'ordine di acquisto eseguito;  anche detto prezzo
     medio effettivo. */
  double		prezzo_medio_eseguito;

  /* Controvalore dell'operazione:  prodotto tra  numero quote  e prezzo
     medio effettivo. */
  double		controvalore_operazione;

  /* Costo dell'operazione di acquisto. */
  double		costo_operazione_acquisto;

  /* Controvalore  totale dell'operazione  di acquisto;  è la  somma che
     esce dal Conto Corrente ed entra nel Conto Titoli. */
  double		controvalore_totale;

  /* Prezzo  medio di  carico  di una  quota  acquistata.  Rapporto  tra
     controvalore totale e numero quote acquistate. */
  double		prezzo_medio_carico;
};

void
operazione_acquisto_init (operazione_acquisto_t * const O)
/* I  seguenti  campi della  struttura  O  devono essere  inizializzati:
   numero_ordine, numero_quote, prezzo_medio_eseguito. */
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
  fprintf(stream, "-- Operazione %u (%s): acquisto\n\n", O->numero_ordine,
	  ((O->data_operazione)? O->data_operazione : "nessuna data"));
  fprintf(stream, "%-40s= %10u\n",		"numero d'ordine",		O->numero_ordine);
  fprintf(stream, "%-40s= %10.0f\n",		"numero quote",			O->numero_quote);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"prezzo medio eseguito",	O->prezzo_medio_eseguito);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"controvalore dell'operazione",	O->controvalore_operazione);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"costo dell'operazione",	O->costo_operazione_acquisto);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"controvalore totale",		O->controvalore_totale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"prezzo medio di carico",	O->prezzo_medio_carico);
  fprintf(stream, "\n");
}

void
saldo_acquisto_init (saldo_t * const S, operazione_acquisto_t const * const O, saldo_t const * const S_precedente)
{
  S->numero_ordine		= O->numero_ordine;
  S->numero_quote		= O->numero_quote + S_precedente->numero_quote;
  S->data_operazione		= O->data_operazione;
  S->prezzo_medio_effettivo	= media_ponderata_2(O->numero_quote, O->prezzo_medio_eseguito,
						    S_precedente->numero_quote, S_precedente->prezzo_medio_effettivo);
  S->prezzo_medio_carico	= media_ponderata_2(O->numero_quote, O->prezzo_medio_carico,
						    S_precedente->numero_quote, S_precedente->prezzo_medio_carico);
  S->costo_medio_acquisti	= S->prezzo_medio_carico - S->prezzo_medio_effettivo;
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

  /* Data  dell'operazione  di  vendita.   È  usata  per  arricchire  la
     descrizione.  Questo  campo può essere  impostata a NULL se  non si
     vuole specificare una data. */
  char const *		data_operazione;

  /* Numero quote vendute. */
  double		numero_quote;

  /* Prezzo medio  dell'ordine di  vendita eseguito; anche  detto prezzo
     medio effettivo. */
  double		prezzo_medio_eseguito;

  /* Controvalore dell'operazione:  prodotto tra  numero quote  e prezzo
     medio effettivo. */
  double		controvalore_operazione;

  /* Reddito da capitale dell'operazione  di vendita, rispetto al prezzo
     medio effettivo nel saldo. */
  double		reddito_da_capitale;

  /* Redditi  diversi  dovuti  alla  vendita  di  quote.   È  un  numero
     negativo. */
  double		redditi_diversi;

  /* Tassa sul reddito da capitale. */
  double		tassa_sul_reddito_da_capitale;

  /* Costo  convenzionale   dell'operazione  di  acquisto   delle  quote
     vendute: prodotto  tra quote vendute  e costo medio  degli acquisti
     nel saldo. */
  double		costo_convenzionale_acquisto;

  /* Costo dell'operazione di vendita. */
  double		costo_operazione_vendita;

  /* Controvalore totale dell'operazione: differenza tra il controvalore
     dell'operazione e la somma tra costo  e tassa.  È la somma che esce
     dal Conto Titoli ed entra nel Conto Corrente. */
  double		controvalore_totale;

  /* Prezzo medio netto  di vendita: rapporto tra  controvalore totale e
     numero di quote vendute. */
  double		prezzo_medio_netto;

  /* Rendimento percentuale di questa vendita al lordo di costi e tasse.
     È il valore  che sarebbe mostrato nella tabella  del patrimonio sul
     sito home banking. */
  double		utile_perdita_percentuale;

  /* Rendimento in valuta  di questa vendita al lordo di  costi e tasse.
     È il valore  che sarebbe mostrato nella tabella  del patrimonio sul
     sito home banking. */
  double		utile_perdita_in_valuta;

  /* Rendimento percentuale  di questa vendita rispetto  al prezzo medio
     di carico nel saldo. */
  double		rendimento_percentuale;

  /* Rendimento in valuta di questa  vendita rispetto al prezzo medio di
     carico nel saldo. */
  double		rendimento_in_valuta;
};

void
operazione_vendita_init (operazione_vendita_t * const O, saldo_t const * const S_precedente)
/* I  seguenti  campi della  struttura  O  devono essere  inizializzati:
   numero_ordine, numero_quote, prezzo_medio_eseguito. */
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
  O->costo_convenzionale_acquisto	= O->numero_quote * (S_precedente->prezzo_medio_carico - S_precedente->prezzo_medio_effettivo);
  O->costo_operazione_vendita		= 0.50 + 2.50 + 0.0024 * O->controvalore_operazione;
  O->controvalore_totale		= O->controvalore_operazione - (O->costo_operazione_vendita + O->tassa_sul_reddito_da_capitale);
  O->prezzo_medio_netto			= O->controvalore_totale / O->numero_quote;

  O->utile_perdita_percentuale		= calcolo_rendimento_percentuale(O->prezzo_medio_eseguito, S_precedente->prezzo_medio_carico);
  O->utile_perdita_in_valuta		= O->numero_quote * (O->prezzo_medio_eseguito - S_precedente->prezzo_medio_carico);

  O->rendimento_percentuale		= calcolo_rendimento_percentuale(O->prezzo_medio_netto, S_precedente->prezzo_medio_carico);
  O->rendimento_in_valuta		= O->numero_quote * (O->prezzo_medio_netto - S_precedente->prezzo_medio_carico);

  O->redditi_diversi			=
    ((reddito_vendita - (O->costo_convenzionale_acquisto + O->costo_operazione_vendita)) - reddito_vendita)
    + ((reddito_vendita > 0.0)? 0.0 : reddito_vendita);
}

void
operazione_vendita_print_ascii (FILE * stream, operazione_vendita_t const * const O)
{
  fprintf(stream, "-- Operazione %u (%s): vendita\n\n", O->numero_ordine,
	  ((O->data_operazione)? O->data_operazione : "nessuna data"));
  fprintf(stream, "%-40s= %10u\n",		"numero d'ordine",			O->numero_ordine);
  fprintf(stream, "%-40s= %10.0f\n",		"numero quote",				O->numero_quote);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"prezzo medio eseguito",		O->prezzo_medio_eseguito);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"controvalore dell'operazione",		O->controvalore_operazione);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"controvalore totale",			O->controvalore_totale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"prezzo medio netto",			O->prezzo_medio_netto);
  fprintf(stream, "\n");
  fprintf(stream, "%-40s= %10.2f EUR\n",	"reddito da capitale",			O->reddito_da_capitale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"tasse sul reddito",			O->tassa_sul_reddito_da_capitale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"costo dell'operazione di vendita",	O->costo_operazione_vendita);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"costo convenzionale di acquisto",	O->costo_convenzionale_acquisto);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"redditi diversi",			O->redditi_diversi);
  fprintf(stream, "\n");
  fprintf(stream, "%-40s= %12.4f%%\n",		"Utile/Perdita percentuale",		O->utile_perdita_percentuale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"Utile/Perdita in valuta",		O->utile_perdita_in_valuta);
  fprintf(stream, "%-40s= %12.4f%%\n",		"rendimento percentuale",		O->rendimento_percentuale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"rendimento in valuta",			O->rendimento_in_valuta);
  fprintf(stream, "\n");
}

void
saldo_vendita_init (saldo_t * const S, operazione_vendita_t const * const O, saldo_t const * const S_precedente)
{
  S->numero_ordine		= O->numero_ordine;
  S->numero_quote		= S_precedente->numero_quote - O->numero_quote;
  S->data_operazione		= O->data_operazione;
  if (S->numero_quote > 0) {
    S->prezzo_medio_effettivo	= S_precedente->prezzo_medio_effettivo;
    S->prezzo_medio_carico	= S_precedente->prezzo_medio_carico;
    S->costo_medio_acquisti	= S->prezzo_medio_carico - S->prezzo_medio_effettivo;
    S->controvalore_carico	= S->numero_quote * S->prezzo_medio_carico;
  } else {
    S->prezzo_medio_effettivo	= 0.0;
    S->prezzo_medio_carico	= 0.0;
    S->costo_medio_acquisti	= 0.0;
    S->controvalore_carico	= 0.0;
  }
  S->minusvalenze_accumulate	= S_precedente->minusvalenze_accumulate - O->redditi_diversi;
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
    char const *	data_operazione;
    double		numero_quote;
    double		prezzo_medio_eseguito;
  };
};

void
operazione_init (operazione_t * const O, saldo_t const * const S_precedente)
/* I seguenti campi della struttura O devono essere inizializzati: tipo,
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
saldo_init (saldo_t * const S, operazione_t const * const O, saldo_t const * const S_precedente)
/* I seguenti campi della struttura O devono essere inizializzati: tipo,
   numero_quote, prezzo_medio_eseguito. */
{
  if (ACQUISTO == O->tipo) {
    saldo_acquisto_init (S, &(O->acquisto), S_precedente);
  } else {
    saldo_vendita_init  (S, &(O->vendita),  S_precedente);
  }
}


/** --------------------------------------------------------------------
 ** Type definition: nota di ordine eseguito.
 ** ----------------------------------------------------------------- */

typedef struct nota_eseguito_t		nota_eseguito_t;

/* Dopo ogni  operazione di  compravendita: nella sezione  documenti del
 * sito  di home  banking  è  disponibile una  "Nota  di eseguito",  che
 * riporta tutti i  dati dell'operazione.  È utile  confrontare i valori
 * calcolati nella  struttura "oprazione_t"  con i dati  riportati nella
 * nota.
 *
 * Una  nota   di  eseguito  per   un'ordine  di  acquisto   può  essere
 * inizializzata come:
 *
 *    nota_eseguito_t N = {
 *      .numero_ordine			= 1,
 *      .tipo				= ACQUISTO,
 *      .numero_quote			= 105.0,
 *      .prezzo_medio_eseguito		= +47.46,
 *      .controvalore_operazione	= +4983.30,
 *      .costo_operazione		= 0.50 + 2.50 + 11.96,
 *      .tassa_sul_reddito_da_capitale	= nan(""),
 *      .controvalore_totale		= +4998.26,
 *      .nav_prezzo_medio_carico	= nan(""),
 *    };
 *
 * Una  nota   di  eseguito   per  un'ordine   di  vendita   può  essere
 * inizializzata come:
 *
 *    nota_eseguito_t N = {
 *      .numero_ordine			= 6,
 *      .tipo				= VENDITA,
 *      .numero_quote			= 105.0,
 *      .prezzo_medio_eseguito		= 50.13,
 *      .controvalore_operazione	= 5263.65,
 *      .costo_operazione		= 0.50 + 2.50 + 12.63,
 *      .tassa_sul_reddito_da_capitale	= 73.20,
 *      .controvalore_totale		= 5174.82,
 *      .nav_prezzo_medio_carico	= 47.4487,
 *   };
 */
struct nota_eseguito_t {
  /* Numero  d'ordine  dell'operazione:  1,  2,  3,  ...;  è  un  intero
     strettamente   positivo   che    identifica   univocamente   questa
     compravendita.  È obbligatorio  mantenere correttamente l'ordine in
     cui le compravendite sono eseguite. */
  unsigned		numero_ordine;

  tipo_operazione_t	tipo;

  /* Data  dell'operazione  descritta  da  questa  nota.   È  usata  per
     arricchire  la descrizione.   Questo campo  può essere  impostata a
     NULL se non si vuole specificare una data. */
  char const *		data_operazione;

  /* Numero  quote  acquistate  o  vendute;  è  un  intero  strettamente
     positivo.  La rappresentazione come "double" è per comodità. */
  double		numero_quote;

  /* Prezzo medio di una singola  quota dell'ordine eseguito di acquisto
     o vendita. */
  double		prezzo_medio_eseguito;

  /* Controvalore dell'operazione.  Prodotto tra il numero di quote e il
     prezzo medio eseguito per ogni quota. */
  double		controvalore_operazione;

  /* Costo dell'operazione.   Costi, spese  e commissioni da  pagare per
     eseguire l'acquisto o la vendita. */
  double		costo_operazione;

  /* Se  l'operazione è  una vendita:  tasse  da pagare  sul reddito  da
     capitale.

     Se  l'operazione è  un'acquisto: il  valore di  questo campo  è non
     specificato e non è presente nelle note di eseguito. */
  double		tassa_sul_reddito_da_capitale;

  /* Controvalore totale dell'operazione.
   *
   * - Se  l'operazione  è  un'acquisto:  il controvalore  totale  è  la
   *   quantità di denaro che esce dal Conto Corrente ed entra nel Conto
   *   Titoli.   È pari  al  controvalore dell'operazione  piú il  costo
   *   dell'operazione.
   *
   * - Se  l'operazione  è una  vendita:  il  controvalore totale  è  la
   *   quantità di denaro  che esce dal Conto Titoli ed  entra nel Conto
   *   Corrente.  È  pari al controvalore dell'operazione  meno il costo
   *   dell'operazione, meno le tasse sul reddito da capitale.
   */
  double		controvalore_totale;

  /* Se l'operazione è una vendita: il  NAV del prezzo medio di carico è
     la  media  ponderata dei  prezzi  medi  di  eseguito di  tutti  gli
     acquisti precedenti  il saldo; è usato  nel calcolo dell'imponibile
     su cui pagare le tasse sui redditi.

     Se l'operazione è un acquisto: il valore non è riportato nelle note
     di eseguito. */
  double		nav_prezzo_medio_carico;
};

bool nota_eseguito_confronto__acquisto (nota_eseguito_t const * N, operazione_acquisto_t const * O, saldo_t const * S);
bool nota_eseguito_confronto__vendita  (nota_eseguito_t const * N, operazione_vendita_t  const * O, saldo_t const * S);

bool
nota_eseguito_confronto (nota_eseguito_t const * N, operazione_t const * O, saldo_t const * S)
{
  if (N->numero_ordine != O->numero_ordine) {
    fprintf(stderr, "%s: nota %u, differenti numeri d'ordine tra nota (%u) e operazione (%u)\n",
	    __func__, N->numero_ordine,
	    N->numero_ordine, O->numero_ordine);
    return false;
  }

  if (N->numero_ordine != S->numero_ordine) {
    fprintf(stderr, "%s: nota %u, differenti numeri d'ordine tra nota (%u) e saldo (%u)\n",
	    __func__, N->numero_ordine,
	    N->numero_ordine, S->numero_ordine);
    return false;
  }

  if (N->tipo != O->tipo) {
    fprintf(stderr, "%s: nota %u, la nota è di %s, mentre la operazione è %s\n",
	    __func__, N->numero_ordine,
	    (ACQUISTO == N->tipo)? "un acquisto" : "una vendita",
	    (ACQUISTO == O->tipo)? "un acquisto" : "una vendita");
    return false;
  }

  if (N->numero_quote != O->numero_quote) {
    fprintf(stderr, "%s: nota %u, differenti numeri di quote tra nota (%.0f) e operazione (%.0f)\n",
	    __func__, N->numero_ordine,
	    N->numero_quote, O->numero_quote);
    return false;
  }

  if (N->prezzo_medio_eseguito != O->prezzo_medio_eseguito) {
    fprintf(stderr, "%s: nota %u, differenti prezzi medi eseguiti tra nota (%.4f) e operazione (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->prezzo_medio_eseguito, O->prezzo_medio_eseguito);
    return false;
  }

  if (ACQUISTO == N->tipo) {
    return nota_eseguito_confronto__acquisto (N, &(O->acquisto), S);
  } else {
    return nota_eseguito_confronto__vendita  (N, &(O->vendita),  S);
  }
}

bool
nota_eseguito_confronto__acquisto (nota_eseguito_t const * N, operazione_acquisto_t const * O, saldo_t const * S)
{
  assert(ACQUISTO == N->tipo);

  if (! compare_double(N->controvalore_operazione, O->controvalore_operazione)) {
    fprintf(stderr, "%s: nota %u, differenti controvalori operazione tra nota (%.4f) e operazione (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->controvalore_operazione, O->controvalore_operazione);
    return false;
  }

  if (! compare_double(N->costo_operazione, O->costo_operazione_acquisto)) {
    fprintf(stderr, "%s: nota %u, differenti costi operazione tra nota (%.4f) e operazione (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->costo_operazione, O->costo_operazione_acquisto);
  }

  if (! compare_double(N->controvalore_totale, O->controvalore_totale)) {
    fprintf(stderr, "%s: nota %u, differenti controvalori totali tra nota (%.4f) e operazione (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->controvalore_totale, O->controvalore_totale);
    return false;
  }

  if (NULL == N->data_operazione) {
    printf("Corretto confronto fra nota di eseguito %u, operazione di acquisto e saldo.\n", N->numero_ordine);
  } else {
    printf("Corretto confronto fra nota di eseguito %u (%s), operazione di acquisto e saldo.\n",
	   N->numero_ordine, N->data_operazione);
  }
  return true;
}

bool
nota_eseguito_confronto__vendita  (nota_eseguito_t const * N, operazione_vendita_t  const * O, saldo_t const * S)
{
  assert(VENDITA == N->tipo);

  if (! compare_double(N->controvalore_operazione, O->controvalore_operazione)) {
    fprintf(stderr, "%s: nota %u, differenti controvalori operazione tra nota (%.4f) e operazione (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->controvalore_operazione, O->controvalore_operazione);
    return false;
  }

  if (! compare_double(N->costo_operazione, O->costo_operazione_vendita)) {
    fprintf(stderr, "%s: nota %u, differenti costi operazione tra nota (%.4f) e operazione (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->costo_operazione, O->costo_operazione_vendita);
  }

  if (! compare_double(N->tassa_sul_reddito_da_capitale, O->tassa_sul_reddito_da_capitale)) {
    fprintf(stderr, "%s: nota %u, differenti tasse sul reddito tra nota (%.4f) e operazione (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->tassa_sul_reddito_da_capitale, O->tassa_sul_reddito_da_capitale);
    return false;
  }

  if (! compare_double(N->controvalore_totale, O->controvalore_totale)) {
    fprintf(stderr, "%s: nota %u, differenti controvalori totali tra nota (%.4f) e operazione (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->controvalore_totale, O->controvalore_totale);
    return false;
  }


  if (! compare_double(N->nav_prezzo_medio_carico, S->prezzo_medio_effettivo)) {
    fprintf(stderr, "%s: nota %u, differenti NAV del prezzo medio di carico tra nota (%.4f) e saldo (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->nav_prezzo_medio_carico, S->prezzo_medio_effettivo);
    return false;
  }

  if (NULL == N->data_operazione) {
    printf("Corretto confronto fra nota di eseguito %u, operazione di vendita e saldo.\n", N->numero_ordine);
  } else {
    printf("Corretto confronto fra nota di eseguito %u (%s), operazione di vendita e saldo.\n",
	   N->numero_ordine, N->data_operazione);
  }
  return true;
}


/** --------------------------------------------------------------------
 ** Calcolo storico.
 ** ----------------------------------------------------------------- */

void
operazione_e_saldo (operazione_t * O, saldo_t * S, saldo_t const * const S_precedente)
{
  operazione_init(O, S_precedente);
  saldo_init(S, O, S_precedente);

  operazione_print_ascii(stdout, O);
  saldo_print_ascii(stdout, S);
}

void
calcolo_storico (unsigned numero_operazioni, operazione_t * O, saldo_t * S)
{
  saldo_print_ascii(stdout, &saldo_precedente_convenzionale);
  operazione_e_saldo(&O[0], &S[0], &saldo_precedente_convenzionale);
  for (unsigned i=1; i<numero_operazioni; ++i) {
    operazione_e_saldo(&O[i], &S[i], &S[i-1]);
  }
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* CONTO_INTESA__CALCOLI_ESEMPIO_H */

/* end of file */
