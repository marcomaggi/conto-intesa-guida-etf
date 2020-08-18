/* conto-intesa--calcoli-esempio--rendimento-riepilogo.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli  di  esempio nella  guida,  per  la sezione  "Rendimento
	indicato nel riepilogo del patrimonio".

   Copyright (C) 2017, 2018, 2020 Marco Maggi <mrc.mgg@gmail.com>

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


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{

  setlocale(LC_ALL, "it_IT");
  printf("\n*** Calcoli per gli esempi nella guida: sezione \"Rendimento indicato nel riepilogo del patrimonio\"\n\n");

  printf("** Vendita con guadagno\n");
  {
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	2
    operazione_t	O[NUMERO_OPERAZIONI] = {
      {
	.numero_ordine		= 1,
	.tipo			= ACQUISTO,
	.numero_quote		= 100.00,
	.prezzo_medio_eseguito	= 50.00,
      },
      {
	.numero_ordine		= 2,
	.tipo			= VENDITA,
	.numero_quote		= 100.00,
	.prezzo_medio_eseguito	= 52.00,
      },
    };
    saldo_t	S[NUMERO_OPERAZIONI];

    calcolo_storico(NUMERO_OPERAZIONI, O, S);
  }

  printf("** Vendita con perdita\n");
  {
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	2
    operazione_t	O[NUMERO_OPERAZIONI] = {
      {
	.numero_ordine		= 1,
	.tipo			= ACQUISTO,
	.numero_quote		= 100.00,
	.prezzo_medio_eseguito	= 50.00,
      },
      {
	.numero_ordine		= 2,
	.tipo			= VENDITA,
	.numero_quote		= 100,
	.prezzo_medio_eseguito	= 48.00,
      }
    };
    saldo_t	S[NUMERO_OPERAZIONI];

    calcolo_storico(NUMERO_OPERAZIONI, O, S);
    calcolo_storico_print_ascii(stdout, NUMERO_OPERAZIONI, O, S);
  }

  fflush(stdout);
  exit(EXIT_SUCCESS);
}

/* end of file */
