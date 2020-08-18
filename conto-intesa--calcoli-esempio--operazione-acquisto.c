/* conto-intesa--calcoli-esempio--operazione-acquisto.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di esempio nella guida,  per la sezione "Descrizione di un'operazione
	di acquisto".

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
#include <locale.h>


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

static bool print_latex_output = false;
static void esempio_operazione_acquisto (void);

int
main (int argc, const char *const argv[])
{
  if (2 == argc) {
    print_latex_output = true;
  }
  setlocale(LC_ALL, "it_IT");
  printf("\n%%%%%% Calcoli per gli esempi nella guida: sezione \"Descrizione di un'operazione di acquisto\"\n\n");
  esempio_operazione_acquisto();
  exit(EXIT_SUCCESS);
}

void
esempio_operazione_acquisto (void)
{
  double	numero_quote;
  double	prezzo_medio_eseguito;

  {
    double	numero_quote_fase_1	= 20.0;
    double	numero_quote_fase_2	= 30.0;
    double	numero_quote_fase_3	= 50.0;
    double	prezzo_eseguito_fase_1	= 52.0;
    double	prezzo_eseguito_fase_2	= 53.0;
    double	prezzo_eseguito_fase_3	= 55.0;

    if (false == print_latex_output) {
      printf("Fase %u: numero quote=%.0f, prezzo eseguito=%.2f\n", 1, numero_quote_fase_1, prezzo_eseguito_fase_1);
      printf("Fase %u: numero quote=%.0f, prezzo eseguito=%.2f\n", 2, numero_quote_fase_2, prezzo_eseguito_fase_2);
      printf("Fase %u: numero quote=%.0f, prezzo eseguito=%.2f\n", 3, numero_quote_fase_3, prezzo_eseguito_fase_3);
    }
    numero_quote		= numero_quote_fase_1 + numero_quote_fase_2 + numero_quote_fase_3;
    prezzo_medio_eseguito	= media_ponderata_3(numero_quote_fase_1, prezzo_eseguito_fase_1,
						    numero_quote_fase_2, prezzo_eseguito_fase_2,
						    numero_quote_fase_3, prezzo_eseguito_fase_3);
  }

  {
#undef  NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	1
    operazione_t	O[NUMERO_OPERAZIONI] = {
      {
	.numero_ordine		= 1,
	.tipo			= ACQUISTO,
	.numero_quote		= numero_quote,
	.prezzo_medio_eseguito	= prezzo_medio_eseguito,
      },
    };
    saldo_t		S[NUMERO_OPERAZIONI];

    calcolo_storico(NUMERO_OPERAZIONI, O, S);
    if (print_latex_output) {
      calcolo_storico_print_latex(stdout, "EsAcq", NUMERO_OPERAZIONI, O, S);
    } else {
      calcolo_storico_print_ascii(stdout, NUMERO_OPERAZIONI, O, S);
    }
  }
}

/* end of file */
