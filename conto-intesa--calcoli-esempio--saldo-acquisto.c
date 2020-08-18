/* conto-intesa--calcoli-esempio--saldo-acquisto.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di esempio nella guida, per  la sezione "Aggiornamento del saldo dopo
	un'operazione di acquisto".

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
static void esempio_aggiornamento_saldo_dopo_acquisti (void);

int
main (int argc, const char *const argv[])
{
  if (2 == argc) {
    print_latex_output = true;
  }
  setlocale(LC_ALL, "it_IT");
  printf("\n%%%%%% Calcoli per gli esempi nella guida: sezione \"Aggiornamento del saldo dopo un'operazione di acquisto\"\n\n");
  esempio_aggiornamento_saldo_dopo_acquisti();
  exit(EXIT_SUCCESS);
}

void
esempio_aggiornamento_saldo_dopo_acquisti (void)
{
#define NUMERO_OPERAZIONI	3
  operazione_t	O[NUMERO_OPERAZIONI] = {
    {
      .numero_ordine		= 1,
      .tipo			= ACQUISTO,
      .numero_quote		= 101,
      .prezzo_medio_eseguito	= 51.00,
    },
    {
      .numero_ordine		= 2,
      .tipo			= ACQUISTO,
      .numero_quote		= 102,
      .prezzo_medio_eseguito	= 52.00,
    },
    {
      .numero_ordine		= 3,
      .tipo			= ACQUISTO,
      .numero_quote		= 103,
      .prezzo_medio_eseguito	= 53.00,
    }
  };
  saldo_t	S[NUMERO_OPERAZIONI];

  calcolo_storico(NUMERO_OPERAZIONI, O, S);
  if (print_latex_output) {
    calcolo_storico_print_latex(stdout, "EsSaldoAcq", NUMERO_OPERAZIONI, O, S);
  } else {
    calcolo_storico_print_ascii(stdout, NUMERO_OPERAZIONI, O, S);
  }

  printf("%% Calcolo del totale dei costi\n\n");
  {
    double	costo_totale_1 =
      O[0].acquisto.costo_operazione_acquisto +
      O[1].acquisto.costo_operazione_acquisto +
      O[2].acquisto.costo_operazione_acquisto;
    double	costo_totale_2 = S[2].numero_quote * S[2].costo_medio_quote;

    if (print_latex_output) {
      latex_output_config_t		config = {
	.stream		= stdout,
	.ordine		= "tre",
	.prefisso	= "EsSaldoAcq",
	.oggetto	= "Saldo",
      };

      print_latex_newcommand_double_2(&config, "CostoTotaleQuote", costo_totale_2);
    } else {
      printf("%-30s= %10.2f EUR\n", "come somma dei costi",		costo_totale_1);
      printf("%-30s= %10.2f EUR\n", "dal costo medio per quota",	costo_totale_2);
      printf("%-30s= %12.4f EUR\n", "costo medio per quota",		costo_totale_2 / S[2].numero_quote);
    }
  }
}

/* end of file */
