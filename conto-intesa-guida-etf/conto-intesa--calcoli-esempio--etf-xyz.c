/* conto-intesa--calcoli-esempio--etf-xyz.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Jan  4, 2018

   Abstract

	Esempio di compravendite e confronto con note di acquisto.

   Copyright (C) 2018, 2020 Marco Maggi <mrc.mgg@gmail.com>

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
 ** Tabella operazioni.
 ** ----------------------------------------------------------------- */

#define NUMERO_OPERAZIONI	3
operazione_t		O[NUMERO_OPERAZIONI] = {
  {
    .numero_ordine			= 1,
    .tipo				= ACQUISTO,
    .numero_quote			= 39.0,
    .prezzo_medio_eseguito		= +130.0,
  },
  {
    .numero_ordine			= 2,
    .tipo				= ACQUISTO,
    .numero_quote			= 39.0,
    .prezzo_medio_eseguito		= +131.75,
  },
  {
    .numero_ordine			= 3,
    .tipo				= ACQUISTO,
    .numero_quote			= 76.0,
    .prezzo_medio_eseguito		= 131.70,
  },
};
saldo_t		S[NUMERO_OPERAZIONI];


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  setlocale(LC_ALL, "it_IT");
  printf("\n*** Calcoli di esempio: ETF XYZ\n\n");

  calcolo_storico(NUMERO_OPERAZIONI, O, S);
  calcolo_storico_print_ascii(stdout, NUMERO_OPERAZIONI, O, S);
  exit(EXIT_SUCCESS);
}

/* end of file */
