/* conto-intesa--calcoli-esempio--operazione-vendita.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di esempio  nella guida, per la  sezione "Descrizione di
	un'operazione di vendita".

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


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  double	numero_quote;
  double	prezzo_medio_eseguito;

  setlocale(LC_ALL, "it_IT");
  printf("\n*** Calcoli per gli esempi nella guida: sezione \"Descrizione di un'operazione di vendita\"\n\n");

  {
    double	numero_quote_fase_1	= 20.0;
    double	numero_quote_fase_2	= 30.0;
    double	numero_quote_fase_3	= 40.0;
    double	prezzo_fase_1		= 102.0;
    double	prezzo_fase_2		= 103.0;
    double	prezzo_fase_3		= 104.0;

    numero_quote		= numero_quote_fase_1 + numero_quote_fase_2 + numero_quote_fase_3;
    prezzo_medio_eseguito	= media_ponderata_3(numero_quote_fase_1, prezzo_fase_1,
						    numero_quote_fase_2, prezzo_fase_2,
						    numero_quote_fase_3, prezzo_fase_3);
  }

  {
    operazione_t	O[2] = {
      {
	.numero_ordine		= 1,
	.tipo			= ACQUISTO,
	.numero_quote		= 100,
	.prezzo_medio_eseguito	= 100.00,
      },
      {
	.numero_ordine		= 2,
	.tipo			= VENDITA,
	.numero_quote		= numero_quote,
	.prezzo_medio_eseguito	= prezzo_medio_eseguito,
      }
    };
    saldo_t		S[2];
    calcolo_storico(2, O, S);
  }

  fflush(stdout);
  exit(EXIT_SUCCESS);
}

/* end of file */
