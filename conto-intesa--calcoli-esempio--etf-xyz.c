/* conto-intesa--calcoli-esempio--etf-xyz.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Jan  4, 2018

   Abstract

	Esempio di compravendite e confronto con note di acquisto.

   Copyright (C) 2018 Marco Maggi <mrc.mgg@gmail.com>

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
    .data_operazione			= "2020 gennaio 01",
    .numero_quote			= 39.0,
    .prezzo_medio_eseguito		= +130.0,
  },
  {
    .numero_ordine			= 2,
    .tipo				= ACQUISTO,
    .data_operazione			= "2020 febbraio 02",
    .numero_quote			= 39.0,
    .prezzo_medio_eseguito		= +131.75,
  },
  {
    .numero_ordine			= 3,
    .tipo				= ACQUISTO,
    .data_operazione			= "2020 marzo 03",
    .numero_quote			= 76.0,
    .prezzo_medio_eseguito		= 131.70,
  },
};
saldo_t		S[NUMERO_OPERAZIONI];


/** --------------------------------------------------------------------
 ** Tabella note di ordine eseguito.
 ** ----------------------------------------------------------------- */

nota_eseguito_t const	N[NUMERO_OPERAZIONI] = {
  {
    .numero_ordine			= 1,
    .tipo				= ACQUISTO,
    .data_operazione			= "2020 gennaio 01",
    .numero_quote			= 39.0,
    .prezzo_medio_eseguito		= +130.0,
    .controvalore_operazione		= +5070.00,
    .costo_operazione			= 0.50 + 2.50 + 12.17,
    .tassa_sul_reddito_da_capitale	= nan(""),
    .controvalore_totale		= +5085.17,
    .nav_prezzo_medio_carico		= nan(""),
  },
  {
    .numero_ordine			= 2,
    .tipo				= ACQUISTO,
    .data_operazione			= "2020 febbraio 02",
    .numero_quote			= 39.0,
    .prezzo_medio_eseguito		= +131.75,
    .controvalore_operazione		= 5138.25,
    .costo_operazione			= 0.50 + 2.50 + 12.33,
    .tassa_sul_reddito_da_capitale	= nan(""),
    .controvalore_totale		= 5153.58,
    .nav_prezzo_medio_carico		= nan(""),
  },
  {
    .numero_ordine			= 3,
    .tipo				= ACQUISTO,
    .data_operazione			= "2020 marzo 03",
    .numero_quote			= 76.0,
    .prezzo_medio_eseguito		= 131.70,
    .controvalore_operazione		= 10009.20,
    .costo_operazione			= 0.50 + 2.50 + 24.02,
    .tassa_sul_reddito_da_capitale	= nan(""),
    .controvalore_totale		= 10036.22,
    .nav_prezzo_medio_carico		= nan(""),
  },
};


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  setlocale(LC_ALL, "it_IT");
  printf("\n*** Calcoli di esempio: ETF XYZ\n\n");

  calcolo_storico(NUMERO_OPERAZIONI, O, S);
  fflush(stdout);

  printf("\n");

  for (int i=0; i<NUMERO_OPERAZIONI; ++i) {
    nota_eseguito_confronto(&N[i], &O[i], &S[i]);
  }

  fflush(stdout);
  exit(EXIT_SUCCESS);
}

/* end of file */
