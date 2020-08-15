/* conto-intesa--calcoli-esempio--strategie-prezzi.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di esempio  nella guida, per la sezione "Strategie  per la scelta dei
	prezzi di vendita".

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


/* ------------------------------------------------------------------ */
/* Headers.                                                           */
/* ------------------------------------------------------------------ */

#include "conto-intesa--calcoli-esempio.h"
#include <math.h>
#include <locale.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Function prototypes.
 ** ----------------------------------------------------------------- */

static void strategia_linee_investimento (void);
static void risultato_compravendita_linea_di_investimento (char const * descr, operazione_t * _acq, operazione_t * _ven);


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  setlocale(LC_ALL, "it_IT");
  printf("\n*** Calcoli per gli esempi nella guida: sezione \"Strategie per la scelta dei prezzi di vendita\"\n\n");
  strategia_linee_investimento();
  exit(EXIT_SUCCESS);
}


/** --------------------------------------------------------------------
 ** Strategia di accoppiamento diretto tra acquisti e vendite.
 ** ----------------------------------------------------------------- */

void
strategia_linee_investimento (void)
{
  double	capitale_1	= 5000.00;
  double	capitale_2	= 5000.00;
  double	capitale_3	= 5000.00;

  double	prezzo_medio_effettivo_acquisto_1	= 40.0;
  double	prezzo_medio_effettivo_acquisto_2	= 50.0;
  double	prezzo_medio_effettivo_acquisto_3	= 60.0;

  double	prezzo_medio_effettivo_vendita_1	= 46.0;
  double	prezzo_medio_effettivo_vendita_2	= 49.50;
  double	prezzo_medio_effettivo_vendita_3	= 65.0;

  double	numero_quote_1	= capitale_1 / prezzo_medio_effettivo_acquisto_1;
  double	numero_quote_2	= capitale_2 / prezzo_medio_effettivo_acquisto_2;
  double	numero_quote_3	= capitale_3 / prezzo_medio_effettivo_acquisto_3;

  printf("numero quote non arrotondato 1: %f/%f=%f\n", capitale_1, prezzo_medio_effettivo_acquisto_1, numero_quote_1);
  printf("numero quote non arrotondato 2: %f/%f=%f\n", capitale_2, prezzo_medio_effettivo_acquisto_2, numero_quote_2);
  printf("numero quote non arrotondato 3: %f/%f=%f\n", capitale_3, prezzo_medio_effettivo_acquisto_3, numero_quote_3);

  numero_quote_1	= floor(numero_quote_1);
  numero_quote_2	= floor(numero_quote_2);
  numero_quote_3	= floor(numero_quote_3);

  printf("numero quote arrotondato 1: %f\n", numero_quote_1);
  printf("numero quote arrotondato 2: %f\n", numero_quote_2);
  printf("numero quote arrotondato 3: %f\n", numero_quote_3);

  printf("\n");

#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	6
  operazione_t	O[NUMERO_OPERAZIONI] = {
    {
      .numero_ordine		= 1,
      .tipo			= ACQUISTO,
      .data_operazione		= NULL,
      .numero_quote		= numero_quote_1,
      .prezzo_medio_eseguito	= prezzo_medio_effettivo_acquisto_1,
    },
    {
      .numero_ordine		= 2,
      .tipo			= ACQUISTO,
      .data_operazione		= NULL,
      .numero_quote		= numero_quote_2,
      .prezzo_medio_eseguito	= prezzo_medio_effettivo_acquisto_2,
    },
    {
      .numero_ordine		= 3,
      .tipo			= ACQUISTO,
      .data_operazione		= NULL,
      .numero_quote		= numero_quote_3,
      .prezzo_medio_eseguito	= prezzo_medio_effettivo_acquisto_3,
    },
    {
      .numero_ordine		= 4,
      .tipo			= VENDITA,
      .data_operazione		= NULL,
      .numero_quote		= numero_quote_1,
      .prezzo_medio_eseguito	= prezzo_medio_effettivo_vendita_1,
    },
    {
      .numero_ordine		= 5,
      .tipo			= VENDITA,
      .data_operazione		= NULL,
      .numero_quote		= numero_quote_2,
      .prezzo_medio_eseguito	= prezzo_medio_effettivo_vendita_2,
    },
    {
      .numero_ordine		= 6,
      .tipo			= VENDITA,
      .data_operazione		= NULL,
      .numero_quote		= numero_quote_3,
      .prezzo_medio_eseguito	= prezzo_medio_effettivo_vendita_3,
    },
  };
  saldo_t	S[NUMERO_OPERAZIONI];

  calcolo_storico(NUMERO_OPERAZIONI, O, S);
  printf("\n\n");
  fflush(stdout);

  risultato_compravendita_linea_di_investimento("prima",   &(O[0]), &(O[3]));
  risultato_compravendita_linea_di_investimento("seconda", &(O[1]), &(O[4]));
  risultato_compravendita_linea_di_investimento("terza",   &(O[2]), &(O[5]));
}

void
risultato_compravendita_linea_di_investimento (char const * descr, operazione_t * _acq, operazione_t * _ven)
{
  operazione_acquisto_t	*acq = (operazione_acquisto_t *)_acq;
  operazione_vendita_t	*ven = (operazione_vendita_t  *)_ven;

  printf("Rendimento %s linea di investimento (calcolo con i controvalori): 100 * (%.2f - %.2f) / %.2f = %.2f%%\n",
	 descr,
	 ven->controvalore_totale, acq->controvalore_totale, acq->controvalore_totale,
	 calcolo_rendimento_percentuale(ven->controvalore_totale, acq->controvalore_totale));
  printf("Rendimento %s linea di investimento (calcolo con i prezzi medi):  100 * (%.2f - %.2f) / %.2f = %.2f%%\n",
	 descr,
	 ven->prezzo_medio_netto, acq->prezzo_medio_carico, acq->prezzo_medio_carico,
	 calcolo_rendimento_percentuale(ven->prezzo_medio_netto, acq->prezzo_medio_carico));
  printf("\n");
}

/* end of file */
