/* conto-intesa--calcoli-esempio--strategie-prezzi.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di esempio nella guida, per la sezione "Strategie per la
	scelta dei prezzi di vendita".

   Copyright (C) 2017, 2018 Marco Maggi <mrc.mgg@gmail.com>

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
 ** Function prototypes.
 ** ----------------------------------------------------------------- */

static void strategia_accoppiamento_diretto (void);
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

static void strategia_medie_ponderate__esempio_guadagno   (void);
static void strategia_medie_ponderate__esempio_perdita_1  (void);
static void strategia_medie_ponderate__esempio_perdita_2  (void);

void
strategia_medie_ponderate (void)
{
  strategia_medie_ponderate__esempio_guadagno();
  strategia_medie_ponderate__esempio_perdita_1();
  strategia_medie_ponderate__esempio_perdita_2();
  fflush(stdout);
}

void
strategia_medie_ponderate__esempio_guadagno (void)
{
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	2
  operazione_t	O[NUMERO_OPERAZIONI] = {
    {
      .numero_ordine		= 1,
      .tipo			= ACQUISTO,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 50.00,
    },
    {
      .numero_ordine		= 2,
      .tipo			= VENDITA,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 52.00,
    }
  };
  saldo_t	S[NUMERO_OPERAZIONI];

  printf("\n* Metodo delle medie ponderate: esempio di guadagno\n\n");
  calcolo_storico(NUMERO_OPERAZIONI, O, S);
}

void
strategia_medie_ponderate__esempio_perdita_1 (void)
{
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	2
  operazione_t	O[NUMERO_OPERAZIONI] = {
    {
      .numero_ordine		= 1,
      .tipo			= ACQUISTO,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 50.00,
    },
    {
      .numero_ordine		= 2,
      .tipo			= VENDITA,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 50.30,
    }
  };
  saldo_t	S[NUMERO_OPERAZIONI];

  printf("\n* Metodo delle medie ponderate: esempio di perdita 1\n\n");
  calcolo_storico(NUMERO_OPERAZIONI, O, S);
}

void
strategia_medie_ponderate__esempio_perdita_2 (void)
{
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	2
  operazione_t	O[NUMERO_OPERAZIONI] = {
    {
      .numero_ordine		= 1,
      .tipo			= ACQUISTO,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 50.00,
    },
    {
      .numero_ordine		= 2,
      .tipo			= VENDITA,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 48.00,
    }
  };
  saldo_t	S[NUMERO_OPERAZIONI];

  printf("\n* Metodo delle medie ponderate: esempio di perdita 2\n\n");
  calcolo_storico(NUMERO_OPERAZIONI, O, S);
}

/* end of file */
