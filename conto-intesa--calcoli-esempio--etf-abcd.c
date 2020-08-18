/* conto-intesa--calcoli-esempio--etf-abcd.c -*- coding: utf-8-unix -*-

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

#define NUMERO_OPERAZIONI	6
operazione_t		O[NUMERO_OPERAZIONI] = {
  {
    .numero_ordine		= 1,
    .tipo			= ACQUISTO,
    .numero_quote		= 105.0,
    .prezzo_medio_eseguito	= 47.46,
  },
  {
    .numero_ordine		= 2,
    .tipo			= ACQUISTO,
    .numero_quote		= 70.0 + 35.0,
    .prezzo_medio_eseguito	= 47.10,
  },
  {
    .numero_ordine		= 3,
    .tipo			= ACQUISTO,
    .numero_quote		= 105.0,
    .prezzo_medio_eseguito	= 47.30,
  },
  {
    .numero_ordine		= 4,
    .tipo			= ACQUISTO,
    .numero_quote		= 105.0,
    .prezzo_medio_eseguito	= 47.935,
  },
  {
    .numero_ordine		= 5,
    .tipo			= VENDITA,
    .numero_quote		= 210.0,
    .prezzo_medio_eseguito	= 50.18,
  },
  {
    .numero_ordine		= 6,
    .tipo			= VENDITA,
    .numero_quote		= 105,
    .prezzo_medio_eseguito	= 50.13,
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
  printf("\n*** Calcoli di esempio: ETF ABCD\n\n");

  calcolo_storico(NUMERO_OPERAZIONI, O, S);
  calcolo_storico_print_ascii(stdout, NUMERO_OPERAZIONI, O, S);
  exit(EXIT_SUCCESS);
}

/* end of file */
