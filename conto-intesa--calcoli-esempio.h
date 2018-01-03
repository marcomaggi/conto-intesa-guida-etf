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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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


/** --------------------------------------------------------------------
 ** Type definitions: saldo dopo compravendita.
 ** ----------------------------------------------------------------- */

typedef struct saldo_t		saldo_t;

struct saldo_t {
  /* Numero d'ordine dell'operazione precedente a questo saldo. */
  unsigned	numero_ordine;

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
  fprintf(stream, "%-40s= %10u\n",	"numero d'ordine",		S->numero_ordine);
  fprintf(stream, "%-40s= %10.0f\n",	"numero quote",			S->numero_quote);
  fprintf(stream, "%-40s= %10.2f EUR\n", "prezzo medio effettivo",	S->prezzo_medio_effettivo);
  fprintf(stream, "%-40s= %12.4f EUR\n", "costo medio per quota",	S->costo_medio_acquisti);
  fprintf(stream, "%-40s= %10.2f EUR\n", "prezzo medio carico",		S->prezzo_medio_carico);
  fprintf(stream, "%-40s= %10.2f EUR\n", "controvalore di carico",	S->controvalore_carico);
  fprintf(stream, "%-40s= %10.2f EUR\n", "minusvalenze accumulate",	S->minusvalenze_accumulate);
}


/** --------------------------------------------------------------------
 ** Type definitions: operazione acquisto.
 ** ----------------------------------------------------------------- */

typedef struct operazione_acquisto_t	operazione_acquisto_t;

struct operazione_acquisto_t {
  /* Numero d'ordine dell'operazione. */
  unsigned		numero_ordine;

  tipo_operazione_t	tipo;

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
  fprintf(stream, "%-40s= %10u\n",		"numero d'ordine",		O->numero_ordine);
  fprintf(stream, "%-40s= %10.0f\n",		"numero quote",			O->numero_quote);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"prezzo medio eseguito",	O->prezzo_medio_eseguito);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"controvalore dell'operazione",	O->controvalore_operazione);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"costo dell'operazione",	O->costo_operazione_acquisto);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"controvalore totale",		O->controvalore_totale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"prezzo medio di carico",	O->prezzo_medio_carico);
}

void
saldo_acquisto_init (saldo_t * const S, operazione_acquisto_t const * const O, saldo_t const * const S_precedente)
{
  S->numero_ordine		= O->numero_ordine;
  S->numero_quote		= O->numero_quote + S_precedente->numero_quote;
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
  double		tassa_sul_reddito;

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
    O->tassa_sul_reddito		= (O->reddito_da_capitale > 0.0)? (0.26 * O->reddito_da_capitale) : 0.0;
  } else {
    O->reddito_da_capitale		= 0.0;
    O->tassa_sul_reddito		= 0.0;
  }
  O->costo_convenzionale_acquisto	= O->numero_quote * (S_precedente->prezzo_medio_carico - S_precedente->prezzo_medio_effettivo);
  O->costo_operazione_vendita		= 0.50 + 2.50 + 0.0024 * O->controvalore_operazione;
  O->controvalore_totale		= O->controvalore_operazione - (O->costo_operazione_vendita + O->tassa_sul_reddito);
  O->prezzo_medio_netto			= O->controvalore_totale / O->numero_quote;

  O->utile_perdita_percentuale		= calcolo_rendimento_percentuale(O->prezzo_medio_eseguito, S_precedente->prezzo_medio_carico);
  O->utile_perdita_in_valuta		= O->numero_quote * (O->prezzo_medio_eseguito - S_precedente->prezzo_medio_carico);

  O->rendimento_percentuale		= calcolo_rendimento_percentuale(O->prezzo_medio_netto, S_precedente->prezzo_medio_carico);
  O->rendimento_in_valuta		= O->numero_quote * (O->prezzo_medio_netto - S_precedente->prezzo_medio_carico);

  O->redditi_diversi			=
    ((O->reddito_da_capitale - (O->costo_convenzionale_acquisto + O->costo_operazione_vendita)) - O->reddito_da_capitale)
    + (reddito_vendita > 0.0)? 0.0 : reddito_vendita;
}

void
operazione_vendita_print_ascii (FILE * stream, operazione_vendita_t const * const O)
{
  fprintf(stream, "%-40s= %10u\n",		"numero d'ordine",			O->numero_ordine);
  fprintf(stream, "%-40s= %10.0f\n",		"numero quote",				O->numero_quote);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"prezzo medio eseguito",		O->prezzo_medio_eseguito);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"controvalore dell'operazione",		O->controvalore_operazione);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"controvalore totale",			O->controvalore_totale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"prezzo medio netto",			O->prezzo_medio_netto);
  fprintf(stream, "\n");
  fprintf(stream, "%-40s= %10.2f EUR\n",	"reddito da capitale",			O->reddito_da_capitale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"tasse sul reddito",			O->tassa_sul_reddito);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"costo dell'operazione di vendita",	O->costo_operazione_vendita);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"costo medio operazioni acquisto",	O->costo_convenzionale_acquisto);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"redditi diversi",			O->redditi_diversi);
  fprintf(stream, "\n");
  fprintf(stream, "%-40s= %12.4f%%\n",		"Utile/Perdita percentuale",		O->utile_perdita_percentuale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"Utile/Perdita in valuta",		O->utile_perdita_in_valuta);
  fprintf(stream, "%-40s= %12.4f%%\n",		"rendimento percentuale",		O->rendimento_percentuale);
  fprintf(stream, "%-40s= %10.2f EUR\n",	"rendimento in valuta",			O->rendimento_in_valuta);
}

void
saldo_vendita_init (saldo_t * const S, operazione_vendita_t const * const O, saldo_t const * const S_precedente)
{
  S->numero_ordine		= O->numero_ordine;
  S->numero_quote		= S_precedente->numero_quote - O->numero_quote;
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
 ** Calcolo storico.
 ** ----------------------------------------------------------------- */

void
operazione_e_saldo (operazione_t * O, saldo_t * S, saldo_t const * const S_precedente)
{
  operazione_init(O, S_precedente);
  saldo_init(S, O, S_precedente);

  printf("-- Operazione %u: %s\n\n", O->numero_ordine, (ACQUISTO == O->tipo)? "acquisto" : "vendita");
  operazione_print_ascii(stdout, O);
  printf("\n");
  printf("-- Saldo %u\n\n", S->numero_ordine);
  saldo_print_ascii(stdout, S);
  printf("\n");
}

void
calcolo_storico (unsigned numero_operazioni, operazione_t * O, saldo_t * S)
{
  printf("-- Saldo iniziale\n\n");
  saldo_print_ascii(stdout, &saldo_precedente_convenzionale);
  printf("\n");

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
