/* conto-intesa--calcoli-esempio--etf-abcd.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Jan  4, 2018

   Abstract

	Esempio di compravendite e confronto con note di acquisto.

   Copyright (C) 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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
 ** Tabella note di ordine eseguito.
 ** ----------------------------------------------------------------- */

nota_eseguito_t const	N[NUMERO_OPERAZIONI] = {
  {
    .numero_ordine			= 1,
    .tipo				= ACQUISTO,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= +47.46,
    .controvalore_operazione		= +4983.30,
    .costo_operazione			= 0.50 + 2.50 + 11.96,
    .tassa_sul_reddito_da_capitale	= nan(""),
    .controvalore_totale		= +4998.26,
    .nav_prezzo_medio_carico		= nan(""),
  },
  {
    .numero_ordine			= 2,
    .tipo				= ACQUISTO,
    .numero_quote			= 70.0 + 35.0,
    .prezzo_medio_eseguito		= +47.10,
    .controvalore_operazione		= 1648.50 + 3297.00,
    .costo_operazione			= 0.50 + 2.50 + 3.96 + 7.91,
    .tassa_sul_reddito_da_capitale	= nan(""),
    .controvalore_totale		= 1655.46 + 3304.91,
    .nav_prezzo_medio_carico		= nan(""),
  },
  {
    .numero_ordine			= 3,
    .tipo				= ACQUISTO,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= 47.30,
    .controvalore_operazione		= 4966.50,
    .costo_operazione			= 0.50 + 2.50 + 11.92,
    .tassa_sul_reddito_da_capitale	= nan(""),
    .controvalore_totale		= 4981.42,
    .nav_prezzo_medio_carico		= nan(""),

  },
  {
    .numero_ordine			= 4,
    .tipo				= ACQUISTO,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= 47.935,
    .controvalore_operazione		= 5033.18,
    .costo_operazione			= 0.50 + 2.50 + 12.08,
    .tassa_sul_reddito_da_capitale	= nan(""),
    .controvalore_totale		= 5048.26,
    .nav_prezzo_medio_carico		= nan(""),
  },
  {
    .numero_ordine			= 5,
    .tipo				= VENDITA,
    .numero_quote			= 210.0,
    .prezzo_medio_eseguito		= 50.18,
    .controvalore_operazione		= 10537.80,
    .costo_operazione			= 0.50 + 2.50 + 25.29,
    .tassa_sul_reddito_da_capitale	= 149.13,
    .controvalore_totale		= 10360.38,
    .nav_prezzo_medio_carico		= 47.4487,
  },
  {
    .numero_ordine			= 6,
    .tipo				= VENDITA,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= 50.13,
    .controvalore_operazione		= 5263.65,
    .costo_operazione			= 0.50 + 2.50 + 12.63,
    .tassa_sul_reddito_da_capitale	= 73.20,
    .controvalore_totale		= 5174.82,
    .nav_prezzo_medio_carico		= 47.4487,
  },
};


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  setlocale(LC_ALL, "it_IT");
  printf("\n*** Calcoli di esempio: ETF ABCD\n\n");

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
