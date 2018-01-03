/* conto-intesa--calcoli-esempio--strategie-prezzi.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di esempio nella guida, per la sezione "Strategie per la
	scelta dei prezzi di vendita".

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


/* ------------------------------------------------------------------ */
/* Headers.                                                           */
/* ------------------------------------------------------------------ */

#include "conto-intesa--calcoli-esempio.h"
#include <locale.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Type definitions.
 ** ----------------------------------------------------------------- */

typedef struct accoppiamento_t		accoppiamento_t;

struct accoppiamento_t {
  unsigned	numero_ordine_acquisto;
  unsigned	numero_ordine_vendita;
  double	numero_quote;
  double	prezzo_medio_carico_di_acquisto;
  double	prezzo_medio_netto_di_vendita;
  double	rendimento_in_valuta;
  double	rendimento_percentuale;
};


/** --------------------------------------------------------------------
 ** Function prototypes.
 ** ----------------------------------------------------------------- */

static void strategia_accoppiamento_diretto (void);
static void accoppiamento_acquisto_vendita (operazione_acquisto_t const * const acquisto,
					    operazione_vendita_t  const * const vendita,
					    accoppiamento_t * const accoppiamento);

static void strategia_medie_ponderate (void);


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  setlocale(LC_ALL, "it_IT");
  printf("\n*** Calcoli per gli esempi nella guida: sezione \"Strategie per la scelta dei prezzi di vendita\"\n\n");
  strategia_accoppiamento_diretto();
  strategia_medie_ponderate();
  exit(EXIT_SUCCESS);
}


/** --------------------------------------------------------------------
 ** Strategia di accoppiamento diretto tra acquisti e vendite.
 ** ----------------------------------------------------------------- */

static void strategia_accoppiamento_diretto__acquisto (unsigned numero_ordine, double numero_quote,
						       double prezzo_medio_carico_acquisto);
static void strategia_accoppiamento_diretto__vendita (unsigned numero_ordine, double numero_quote,
						      double prezzo_medio_carico_acquisto, double prezzo_medio_netto_vendita);

void
strategia_accoppiamento_diretto (void)
{
  double	numero_quote_1			= 101.0;
  double	numero_quote_2			= 102.0;
  double	numero_quote_3			= 103.0;
  double	prezzo_medio_carico_acquisto_1	= 51.0;
  double	prezzo_medio_carico_acquisto_2	= 52.0;
  double	prezzo_medio_carico_acquisto_3	= 53.0;
  double	prezzo_medio_netto_vendita_1	= 55.1;
  double	prezzo_medio_netto_vendita_2	= 55.2;
  double	prezzo_medio_netto_vendita_3	= 55.3;

  printf("\n* Strategia di accoppiamento diretto tra acquisti e vendite\n\n");

  strategia_accoppiamento_diretto__acquisto(1, numero_quote_1, prezzo_medio_carico_acquisto_1);
  strategia_accoppiamento_diretto__acquisto(2, numero_quote_2, prezzo_medio_carico_acquisto_2);
  strategia_accoppiamento_diretto__acquisto(3, numero_quote_3, prezzo_medio_carico_acquisto_3);

  strategia_accoppiamento_diretto__vendita(4, numero_quote_1, prezzo_medio_carico_acquisto_1, prezzo_medio_netto_vendita_1);
  strategia_accoppiamento_diretto__vendita(5, numero_quote_2, prezzo_medio_carico_acquisto_2, prezzo_medio_netto_vendita_2);
  strategia_accoppiamento_diretto__vendita(6, numero_quote_3, prezzo_medio_carico_acquisto_3, prezzo_medio_netto_vendita_3);

  printf("\n\n");
  fflush(stdout);
}

void
strategia_accoppiamento_diretto__acquisto (unsigned numero_ordine, double numero_quote,
					   double prezzo_medio_carico_acquisto)
{
  double	controvalore_totale_acquisto	= numero_quote * prezzo_medio_carico_acquisto;

  printf("\n-- Operazione %u: acquisto\n\n", numero_ordine);
  printf("%-40s=%7.0f\n",	"numero quote",			numero_quote);
  printf("%-40s=%10.2f EUR\n",	"prezzo medio carico",		prezzo_medio_carico_acquisto);
  printf("%-40s=%10.2f EUR\n",	"controvalore totale",		controvalore_totale_acquisto);
}

void
strategia_accoppiamento_diretto__vendita (unsigned numero_ordine, double numero_quote,
					  double prezzo_medio_carico_acquisto, double prezzo_medio_netto_vendita)
{
  double	controvalore_totale_acquisto	= numero_quote * prezzo_medio_carico_acquisto;
  double	controvalore_totale_vendita	= numero_quote * prezzo_medio_netto_vendita;

  printf("\n-- Operazione %u: vendita\n\n", numero_ordine);
  printf("%-40s=%7.0f\n",	"numero quote",			numero_quote);
  printf("%-40s=%10.2f EUR\n",	"prezzo medio netto",		prezzo_medio_netto_vendita);
  printf("%-40s=%10.2f EUR\n",	"controvalore totale",		controvalore_totale_vendita);
  printf("%-40s=%10.2f%%\n",	"rendimento percentuale",
	 calcolo_rendimento_percentuale(prezzo_medio_netto_vendita, prezzo_medio_carico_acquisto));
  printf("%-40s=%10.2f EUR\n",	"rendimento in valuta dai prezzi medi",
	 (numero_quote * (prezzo_medio_netto_vendita - prezzo_medio_carico_acquisto)));
  printf("%-40s=%10.2f EUR\n",	"rendimento in valuta dai controvalori",
	 controvalore_totale_vendita - controvalore_totale_acquisto);
}


/** --------------------------------------------------------------------
 ** Metodo delle medie ponderate.
 ** ----------------------------------------------------------------- */

void
strategia_medie_ponderate (void)
{
#define NUMERO_OPERAZIONI	6
  operazione_t	O[NUMERO_OPERAZIONI] = {
    {
      .numero_ordine		= 1,
      .tipo			= ACQUISTO,
      .numero_quote		= 101,
      .prezzo_medio_eseguito	= 51.00,
    },
    {
      .numero_ordine		= 2,
      .tipo			= ACQUISTO,
      .numero_quote		= 102,
      .prezzo_medio_eseguito	= 52.00,
    },
    {
      .numero_ordine		= 3,
      .tipo			= ACQUISTO,
      .numero_quote		= 103,
      .prezzo_medio_eseguito	= 53.00,
    },
    {
      .numero_ordine		= 4,
      .tipo			= VENDITA,
      .numero_quote		= 101,
      .prezzo_medio_eseguito	= 54.00,
    },
    {
      .numero_ordine		= 5,
      .tipo			= VENDITA,
      .numero_quote		= 102,
      .prezzo_medio_eseguito	= 55.00,
    },
    {
      .numero_ordine		= 6,
      .tipo			= VENDITA,
      .numero_quote		= 103,
      .prezzo_medio_eseguito	= 56.00,
    },
  };
  saldo_t	S[NUMERO_OPERAZIONI];

  printf("\n* Strategia di accoppiamento diretto tra acquisti e vendite\n\n");
  calcolo_storico(NUMERO_OPERAZIONI, O, S);

  /* Accoppiamenti. */
  {
    accoppiamento_t	accoppiamento_14;
    accoppiamento_t	accoppiamento_25;
    accoppiamento_t	accoppiamento_36;
    double		totale_numero_quote;

    accoppiamento_acquisto_vendita(&O[0].acquisto, &O[3].vendita, &accoppiamento_14);
    accoppiamento_acquisto_vendita(&O[1].acquisto, &O[4].vendita, &accoppiamento_25);
    accoppiamento_acquisto_vendita(&O[2].acquisto, &O[5].vendita, &accoppiamento_36);
    totale_numero_quote =
      accoppiamento_14.numero_quote +
      accoppiamento_25.numero_quote +
      accoppiamento_36.numero_quote;

    /* Metodo calcoli 1: calcolo dei controvalori totali. */
    {

      double		controvalore_totale_carico_di_acquisto;
      double		controvalore_totale_netto_di_vendita;
      double		rendimento_totale_in_valuta;
      double		rendimento_totale_percentuale;

      controvalore_totale_carico_di_acquisto =
	accoppiamento_14.numero_quote * accoppiamento_14.prezzo_medio_carico_di_acquisto +
	accoppiamento_25.numero_quote * accoppiamento_25.prezzo_medio_carico_di_acquisto +
	accoppiamento_36.numero_quote * accoppiamento_36.prezzo_medio_carico_di_acquisto;
      controvalore_totale_netto_di_vendita =
	accoppiamento_14.numero_quote * accoppiamento_14.prezzo_medio_netto_di_vendita +
	accoppiamento_25.numero_quote * accoppiamento_25.prezzo_medio_netto_di_vendita +
	accoppiamento_36.numero_quote * accoppiamento_36.prezzo_medio_netto_di_vendita;

      rendimento_totale_in_valuta =
	accoppiamento_14.rendimento_in_valuta +
	accoppiamento_25.rendimento_in_valuta +
	accoppiamento_36.rendimento_in_valuta;
      rendimento_totale_percentuale =
	calcolo_rendimento_percentuale(controvalore_totale_netto_di_vendita, controvalore_totale_carico_di_acquisto);

      printf("-- Totali accoppiamenti, primo metodo: \n\n");
      printf("%-40s= %7.0f\n",		"numero quote",					totale_numero_quote);
      printf("%-40s= %10.2f EUR\n",	"controvalore totale carico di acquisto",	controvalore_totale_carico_di_acquisto);
      printf("%-40s= %10.2f EUR\n",	"controvalore totale netto di vendita",		controvalore_totale_netto_di_vendita);
      printf("%-40s= %10.2f EUR\n",	"rendimento totale in valuta",			rendimento_totale_in_valuta);
      printf("%-40s= %12.4f%%\n",	"rendimento totale percentuale",		rendimento_totale_percentuale);
      printf("\n");
    }

    /* Metodo calcoli 2: calcolo dei prezzi medi. */
    {
      double		totale_prezzo_medio_carico_di_acquisto;
      double		totale_prezzo_medio_netto_di_vendita;
      double		rendimento_totale_in_valuta;
      double		rendimento_totale_percentuale;

      totale_prezzo_medio_carico_di_acquisto =
	media_ponderata_3(accoppiamento_14.numero_quote, accoppiamento_14.prezzo_medio_carico_di_acquisto,
			  accoppiamento_25.numero_quote, accoppiamento_25.prezzo_medio_carico_di_acquisto,
			  accoppiamento_36.numero_quote, accoppiamento_36.prezzo_medio_carico_di_acquisto);

      totale_prezzo_medio_netto_di_vendita =
	media_ponderata_3(accoppiamento_14.numero_quote, accoppiamento_14.prezzo_medio_netto_di_vendita,
			  accoppiamento_25.numero_quote, accoppiamento_25.prezzo_medio_netto_di_vendita,
			  accoppiamento_36.numero_quote, accoppiamento_36.prezzo_medio_netto_di_vendita);

      rendimento_totale_percentuale =
	calcolo_rendimento_percentuale(totale_prezzo_medio_netto_di_vendita, totale_prezzo_medio_carico_di_acquisto);
      rendimento_totale_in_valuta   =
	totale_numero_quote * (totale_prezzo_medio_netto_di_vendita - totale_prezzo_medio_carico_di_acquisto);

      printf("-- Totali accoppiamenti, secondo metodo: \n\n");
      printf("%-40s= %7.0f\n",		"numero quote",					totale_numero_quote);
      printf("%-40s= %10.2f EUR\n",	"totale prezzo medio carico di acquisto",	totale_prezzo_medio_carico_di_acquisto);
      printf("%-40s= %10.2f EUR\n",	"totale prezzo medio netto di vendita",		totale_prezzo_medio_netto_di_vendita);
      printf("%-40s= %10.2f EUR\n",	"rendimento totale in valuta",			rendimento_totale_in_valuta);
      printf("%-40s= %12.4f%%\n",	"rendimento totale percentuale",		rendimento_totale_percentuale);
      printf("\n");
    }
  }

  fflush(stdout);
}

void
accoppiamento_acquisto_vendita (operazione_acquisto_t const * const acquisto,
				operazione_vendita_t  const * const vendita,
				accoppiamento_t * const accoppiamento)
{
  assert(vendita->numero_quote == acquisto->numero_quote);

  accoppiamento->numero_ordine_acquisto = acquisto->numero_ordine;
  accoppiamento->numero_ordine_vendita	= vendita->numero_ordine;
  accoppiamento->numero_quote		= vendita->numero_quote;
  accoppiamento->prezzo_medio_carico_di_acquisto	= acquisto->prezzo_medio_carico;
  accoppiamento->prezzo_medio_netto_di_vendita		= vendita->prezzo_medio_netto;
  accoppiamento->rendimento_in_valuta	= vendita->numero_quote * (vendita->prezzo_medio_netto - acquisto->prezzo_medio_carico);
  accoppiamento->rendimento_percentuale	= calcolo_rendimento_percentuale(vendita->prezzo_medio_netto, acquisto->prezzo_medio_carico);

  printf("-- Accoppiamento acquisto %u e vendita %u:\n\n",
	 accoppiamento->numero_ordine_acquisto,
	 accoppiamento->numero_ordine_vendita);
  printf("%-40s= %7.0f\n",	"numero quote",				accoppiamento->numero_quote);
  printf("%-40s= %10.2f EUR\n",	"prezzo medio carico di acquisto",	accoppiamento->prezzo_medio_carico_di_acquisto);
  printf("%-40s= %10.2f EUR\n",	"prezzo medio netto di vendita",	accoppiamento->prezzo_medio_netto_di_vendita);
  printf("%-40s= %12.4f%%\n",	"rendimento percentuale",		accoppiamento->rendimento_percentuale);
  printf("%-40s= %10.2f EUR\n",	"rendimento in valuta",			accoppiamento->rendimento_in_valuta);
  printf("\n");
}

/* end of file */
