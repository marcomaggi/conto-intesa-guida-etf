/* conto-intesa--calcoli-esempio--strategie-prezzi.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di esempio nella guida, per la sezione "Strategie per la
	scelta dei prezzi di vendita".

   Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

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
static void accoppiamento_acquisto_vendita (unsigned numero_ordine_acquisto, operazione_acquisto_t const * const acquisto,
					    unsigned numero_ordine_vendita,  operazione_vendita_t  const * const vendita,
					    accoppiamento_t * const accoppiamento);


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  printf("\n*** Calcoli per gli esempi nella guida: sezione \"Strategie per la scelta dei prezzi di vendita\"\n\n");
  strategia_accoppiamento_diretto();
  exit(EXIT_SUCCESS);
}


/** --------------------------------------------------------------------
 ** Strategia di accoppiamento diretto tra acquisti e vendite.
 ** ----------------------------------------------------------------- */

void
strategia_accoppiamento_diretto (void)
{
  operazione_acquisto_t		acquisto_1;
  operazione_acquisto_t		acquisto_2;
  operazione_acquisto_t		acquisto_3;
  operazione_vendita_t		vendita_4;
  operazione_vendita_t		vendita_5;
  operazione_vendita_t		vendita_6;
  saldo_t			saldo_1;
  saldo_t			saldo_2;
  saldo_t			saldo_3;
  saldo_t			saldo_4;
  saldo_t			saldo_5;
  saldo_t			saldo_6;

  double	numero_quote_1			= 100.0;
  double	numero_quote_2			= 101.0;
  double	numero_quote_3			= 102.0;
  double	prezzo_medio_effettivo_1	= 110.0;
  double	prezzo_medio_effettivo_2	= 120.0;
  double	prezzo_medio_effettivo_3	= 130.0;

  printf("\n* Strategia di accoppiamento diretto tra acquisti e vendite\n\n");

  setlocale(LC_ALL, "it_IT");

  saldo_print_ascii(&saldo_precedente_convenzionale, "Saldo iniziale");

  /* Acquisti. */
  {
    operazione_acquisto_init(&acquisto_1, "Operazione 1: acquisto", numero_quote_1, prezzo_medio_effettivo_1);
    saldo_acquisto_init(&saldo_1, "Saldo dopo operazione 1", &acquisto_1, &saldo_precedente_convenzionale);
  }
  {
    operazione_acquisto_init(&acquisto_2, "Operazione 2: acquisto", numero_quote_2, prezzo_medio_effettivo_2);
    saldo_acquisto_init(&saldo_2, "Saldo dopo operazione 2", &acquisto_2, &saldo_1);
  }
  {
    operazione_acquisto_init(&acquisto_3, "Operazione 3: acquisto", numero_quote_3, prezzo_medio_effettivo_3);
    saldo_acquisto_init(&saldo_3, "Saldo dopo operazione 3", &acquisto_3, &saldo_2);
  }

  /* Vendite. */
  {
    double	numero_quote_4			= numero_quote_1;
    double	prezzo_medio_effettivo_4	= prezzo_medio_effettivo_1 + 4.0;
    operazione_vendita_init(&vendita_4, "Operazione 4: vendita", numero_quote_4, prezzo_medio_effettivo_4, &saldo_3);
    saldo_vendita_init(&saldo_4, "Saldo dopo operazione 4", &vendita_4, &saldo_3);
  }
  {
    double	numero_quote_5			= numero_quote_2;
    double	prezzo_medio_effettivo_5	= prezzo_medio_effettivo_2 + 4.0;
    operazione_vendita_init(&vendita_5, "Operazione 5: vendita", numero_quote_5, prezzo_medio_effettivo_5, &saldo_4);
    saldo_vendita_init(&saldo_5, "Saldo dopo operazione 5", &vendita_5, &saldo_4);
  }
  {
    double	numero_quote_6			= numero_quote_3;
    double	prezzo_medio_effettivo_6	= prezzo_medio_effettivo_3 + 7.0;
    operazione_vendita_init(&vendita_6, "Operazione 6: vendita", numero_quote_6, prezzo_medio_effettivo_6, &saldo_5);
    saldo_vendita_init(&saldo_6, "Saldo dopo operazione 6", &vendita_6, &saldo_5);
  }

  /* Accoppiamenti. */
  {
    accoppiamento_t	accoppiamento_14;
    accoppiamento_t	accoppiamento_25;
    accoppiamento_t	accoppiamento_36;

    {
      double		totale_numero_quote;
      double		controvalore_totale_carico_di_acquisto;
      double		controvalore_totale_netto_di_vendita;
      double		rendimento_totale_in_valuta;
      double		rendimento_totale_percentuale;

      accoppiamento_acquisto_vendita(1, &acquisto_1, 4, &vendita_4, &accoppiamento_14);
      accoppiamento_acquisto_vendita(2, &acquisto_2, 5, &vendita_5, &accoppiamento_25);
      accoppiamento_acquisto_vendita(3, &acquisto_3, 6, &vendita_6, &accoppiamento_36);

      totale_numero_quote = accoppiamento_14.numero_quote + accoppiamento_25.numero_quote + accoppiamento_36.numero_quote;
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
      printf("%-40s= %7.0f\n",		"numero quote",				totale_numero_quote);
      printf("%-40s= %10.2f EUR\n",	"controvalore totale di carico",	controvalore_totale_carico_di_acquisto);
      printf("%-40s= %10.2f EUR\n",	"rendimento totale in valuta",		rendimento_totale_in_valuta);
      printf("%-40s= %12.4f%%\n",	"rendimento totale percentuale",	rendimento_totale_percentuale);
      printf("\n");
    }
    {
      double		totale_numero_quote;
      double		totale_prezzo_medio_carico_di_acquisto;
      double		totale_prezzo_medio_netto_di_vendita;
      double		rendimento_totale_in_valuta;
      double		rendimento_totale_percentuale;

      totale_numero_quote = accoppiamento_14.numero_quote + accoppiamento_25.numero_quote + accoppiamento_36.numero_quote;

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
      printf("%-40s= %7.0f\n",		"numero quote",				totale_numero_quote);
      printf("%-40s= %10.2f EUR\n",	"totale prezzo medio carico di acquisto",	totale_prezzo_medio_carico_di_acquisto);
      printf("%-40s= %10.2f EUR\n",	"totale prezzo medio netto di vendita",		totale_prezzo_medio_netto_di_vendita);
      printf("%-40s= %10.2f EUR\n",	"rendimento totale in valuta",		rendimento_totale_in_valuta);
      printf("%-40s= %12.4f%%\n",	"rendimento totale percentuale",	rendimento_totale_percentuale);
      printf("\n");
    }
  }

  fflush(stdout);
}

void
accoppiamento_acquisto_vendita (unsigned numero_ordine_acquisto, operazione_acquisto_t const * const acquisto,
				unsigned numero_ordine_vendita,  operazione_vendita_t  const * const vendita,
				accoppiamento_t * const accoppiamento)
{
  accoppiamento->numero_ordine_acquisto = numero_ordine_acquisto;
  accoppiamento->numero_ordine_vendita	= numero_ordine_vendita;
  accoppiamento->numero_quote		= vendita->numero_quote;
  accoppiamento->prezzo_medio_carico_di_acquisto	= acquisto->prezzo_medio_carico;
  accoppiamento->prezzo_medio_netto_di_vendita		= vendita->prezzo_medio_netto;
  accoppiamento->rendimento_in_valuta	= vendita->numero_quote * (vendita->prezzo_medio_netto - acquisto->prezzo_medio_carico);
  accoppiamento->rendimento_percentuale	= calcolo_rendimento_percentuale(vendita->prezzo_medio_netto, acquisto->prezzo_medio_carico);

  assert(vendita->numero_quote == acquisto->numero_quote);

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
