/* conto-intesa--calcoli-esempio--verifica-prezzo-pareggio.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Aug 20, 2020

   Abstract

	Calcoli di esempio  nella guida, per la sezione "Strategie  per la scelta dei
	prezzi di vendita, metodo della  media ponderata".  Verifica del prezzo medio
	effettivo di vendita in pareggio.

   Copyright (C) 2020 Marco Maggi <mrc.mgg@gmail.com>

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
#include <assert.h>


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

static bool print_latex_output = false;
static void verifica_prezzo_pareggio (void);

int
main (int argc, const char *const argv[])
{
  if (2 == argc) {
    print_latex_output = true;
  }
  setlocale(LC_ALL, "it_IT");
  printf("\n%%%%%% Calcoli per gli esempi nella guida: verifica del prezzo medio effettivo di vendita in pareggio.\n\n");
  verifica_prezzo_pareggio();
  exit(EXIT_SUCCESS);
}

void
verifica_prezzo_pareggio (void)
{
  double	prezzo_di_pareggio;

  {
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	1
    operazione_t	O[NUMERO_OPERAZIONI] = {
      {
	.numero_ordine		= 1,
	.tipo			= ACQUISTO,
	.numero_quote		= 100,
	.prezzo_medio_eseguito	= 50.00,
      },
    };
    saldo_t	S[NUMERO_OPERAZIONI];

    calcolo_storico(NUMERO_OPERAZIONI, O, S);
    prezzo_di_pareggio = S[0].prezzo_medio_effettivo_vendita_in_pareggio;
  }

  {
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	2
    operazione_t	O[NUMERO_OPERAZIONI] = {
      {
	.numero_ordine		= 1,
	.tipo			= ACQUISTO,
	.numero_quote		= 100,
	.prezzo_medio_eseguito	= 50.00,
      },
      {
	.numero_ordine		= 2,
	.tipo			= VENDITA,
	.numero_quote		= 100,
	.prezzo_medio_eseguito	= prezzo_di_pareggio,
      }
    };
    saldo_t	S[NUMERO_OPERAZIONI];

    calcolo_storico(NUMERO_OPERAZIONI, O, S);
    if (print_latex_output) {
      calcolo_storico_print_latex(stdout, "VerificaPareggio", NUMERO_OPERAZIONI, O, S);
    } else {
      calcolo_storico_print_ascii(stdout, NUMERO_OPERAZIONI, O, S);
    }

    assert(compare_double(0.0, O[1].vendita.rendimento_in_valuta));
    assert(compare_double(0.0, O[1].vendita.rendimento_in_valuta));
  }
}

/* end of file */
