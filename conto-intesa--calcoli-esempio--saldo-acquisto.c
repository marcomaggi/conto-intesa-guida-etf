/* conto-intesa--calcoli-esempio--saldo-acquisto.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di  esempio nella  guida, per la  sezione "Aggiornamento
	del saldo dopo un'operazione di acquisto".

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


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  double			numero_quote_1		= 100;
  double			numero_quote_2		= 200;
  double			numero_quote_3		= 300;
  double			prezzo_medio_eseguito_1	= 110.00;
  double			prezzo_medio_eseguito_2	= 120.00;
  double			prezzo_medio_eseguito_3	= 130.00;
  operazione_acquisto_t		acquisto_1;
  operazione_acquisto_t		acquisto_2;
  operazione_acquisto_t		acquisto_3;
  saldo_t			saldo_1;
  saldo_t			saldo_2;
  saldo_t			saldo_3;

  printf("\n*** Calcoli  per gli esempi  nella guida: sezione  \"Aggiornamento del saldo dopo un'operazione di acquisto\"\n\n");

  operazione_acquisto_init(&acquisto_1, "Operazione acquisto 1", numero_quote_1, prezzo_medio_eseguito_1);
  saldo_acquisto_init (&saldo_1, "Saldo dopo l'operazione 1", &acquisto_1, &saldo_precedente_convenzionale);

  operazione_acquisto_init(&acquisto_2, "Operazione acquisto 2", numero_quote_2, prezzo_medio_eseguito_2);
  saldo_acquisto_init (&saldo_2, "Saldo dopo l'operazione 2", &acquisto_2, &saldo_1);

  operazione_acquisto_init(&acquisto_3, "Operazione acquisto 3", numero_quote_3, prezzo_medio_eseguito_3);
  saldo_acquisto_init (&saldo_3, "Saldo dopo l'operazione 3", &acquisto_3, &saldo_2);

  printf("\n-- Calcolo del totale dei costi\n");
  {
    double	costo_totale_1 = acquisto_1.costo_operazione + acquisto_2.costo_operazione + acquisto_3.costo_operazione;
    double	costo_totale_2 = saldo_3.numero_quote * (saldo_3.prezzo_medio_carico - saldo_3.prezzo_medio_effettivo);

    printf("%-30s= %10.2f EUR\n", "come somma dei costi",	costo_totale_1);
    printf("%-30s= %10.2f EUR\n", "dai prezzi medi di carico",	costo_totale_2);
    printf("%-30s= %10.2f EUR\n", "costo medio per quota",	costo_totale_2 / saldo_3.numero_quote);
  }

  fflush(stdout);
  exit(EXIT_SUCCESS);
}

/* end of file */