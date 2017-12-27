/* conto-intesa--calcoli-esempio--rendimento-riepilogo.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli  di  esempio nella  guida,  per  la sezione  "Rendimento
	indicato nel riepilogo del patrimonio".

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
  operazione_vendita_t		vendita;

  printf("\n*** Calcoli per gli esempi nella guida: sezione \"Rendimento indicato nel riepilogo del patrimonio\"\n\n");

  operazione_acquisto_init(&acquisto, "Operazione acquisto preliminare", 100.0, 100.00);
  saldo_acquisto_init(&saldo_iniziale, "Saldo iniziale", &acquisto, &saldo_precedente_convenzionale);

  operazione_vendita_init(&vendita, "Operazione vendita a 105,00 EUR", 100.0, 105.00, &saldo_iniziale);

  operazione_vendita_init(&vendita, "Operazione vendita a 98,00 EUR", 100.0, 98.00, &saldo_iniziale);

  fflush(stdout);
  exit(EXIT_SUCCESS);
}

/* end of file */
