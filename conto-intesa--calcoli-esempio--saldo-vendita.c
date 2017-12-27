/* conto-intesa--calcoli-esempio--saldo-vendita.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di  esempio nella  guida, per la  sezione "Aggiornamento
	del saldo dopo un'operazione di vendita".

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
  operazione_acquisto_t		acquisto;
  saldo_t			saldo_iniziale;
  double			numero_quote_1		= 100;
  double			numero_quote_2		= 200;
  double			numero_quote_3		= 300;
  double			prezzo_medio_eseguito_1	= 110.00;
  double			prezzo_medio_eseguito_2	= 120.00;
  double			prezzo_medio_eseguito_3	= 130.00;
  operazione_vendita_t		vendita_1;
  operazione_vendita_t		vendita_2;
  operazione_vendita_t		vendita_3;
  saldo_t			saldo_1;
  saldo_t			saldo_2;
  saldo_t			saldo_3;

  printf("\n*** Calcoli  per gli esempi  nella guida: sezione  \"Aggiornamento del saldo dopo un'operazione di vendita\"\n\n");

  operazione_acquisto_init(&acquisto, "Operazione acquisto preliminare", 100.0, 100.00);
  saldo_acquisto_init(&saldo_iniziale, "Saldo iniziale", &acquisto, &saldo_precedente_convenzionale);

  operazione_vendita_init(&vendita_1, "Operazione vendita 1", numero_quote_1, prezzo_medio_eseguito_1, &saldo_iniziale);
  saldo_vendita_init(&saldo_1, "Saldo dopo l'operazione 1", &vendita_1, &saldo_iniziale);

  operazione_vendita_init(&vendita_2, "Operazione vendita 2", numero_quote_2, prezzo_medio_eseguito_2, &saldo_1);
  saldo_vendita_init(&saldo_2, "Saldo dopo l'operazione 2", &vendita_2, &saldo_1);

  operazione_vendita_init(&vendita_3, "Operazione vendita 3", numero_quote_3, prezzo_medio_eseguito_3, &saldo_2);
  saldo_vendita_init (&saldo_3, "Saldo dopo l'operazione 3", &vendita_3, &saldo_2);

  fflush(stdout);
  exit(EXIT_SUCCESS);
}

/* end of file */
