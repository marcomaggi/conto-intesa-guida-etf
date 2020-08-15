/* conto-intesa--calcoli-esempio--strategie-prezzi.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di esempio  nella guida, per la sezione "Strategie  per la scelta dei
	prezzi di vendita".

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
#include <assert.h>


/** --------------------------------------------------------------------
 ** Function prototypes.
 ** ----------------------------------------------------------------- */

static void strategia_medie_ponderate (void);


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  setlocale(LC_ALL, "it_IT");
  printf("\n*** Calcoli per gli esempi nella guida: sezione \"Strategie per la scelta dei prezzi di vendita\"\n\n");
  strategia_medie_ponderate();
  exit(EXIT_SUCCESS);
}


/** --------------------------------------------------------------------
 ** Metodo delle medie ponderate.
 ** ----------------------------------------------------------------- */

static void strategia_medie_ponderate__esempio_guadagno   (void);
static void strategia_medie_ponderate__esempio_perdita_1  (void);
static void strategia_medie_ponderate__esempio_perdita_2  (void);

void
strategia_medie_ponderate (void)
{
  strategia_medie_ponderate__esempio_guadagno();
  strategia_medie_ponderate__esempio_perdita_1();
  strategia_medie_ponderate__esempio_perdita_2();
  fflush(stdout);
}

void
strategia_medie_ponderate__esempio_guadagno (void)
{
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	2
  operazione_t	O[NUMERO_OPERAZIONI] = {
    {
      .numero_ordine		= 1,
      .tipo			= ACQUISTO,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 50.00,
    },
    {
      .numero_ordine		= 2,
      .tipo			= VENDITA,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 52.00,
    }
  };
  saldo_t	S[NUMERO_OPERAZIONI];

  printf("\n* Metodo delle medie ponderate: esempio di guadagno\n\n");
  calcolo_storico(NUMERO_OPERAZIONI, O, S);
}

void
strategia_medie_ponderate__esempio_perdita_1 (void)
{
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	2
  operazione_t	O[NUMERO_OPERAZIONI] = {
    {
      .numero_ordine		= 1,
      .tipo			= ACQUISTO,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 50.00,
    },
    {
      .numero_ordine		= 2,
      .tipo			= VENDITA,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 50.30,
    }
  };
  saldo_t	S[NUMERO_OPERAZIONI];

  printf("\n* Metodo delle medie ponderate: esempio di perdita 1\n\n");
  calcolo_storico(NUMERO_OPERAZIONI, O, S);
}

void
strategia_medie_ponderate__esempio_perdita_2 (void)
{
#undef NUMERO_OPERAZIONI
#define NUMERO_OPERAZIONI	2
  operazione_t	O[NUMERO_OPERAZIONI] = {
    {
      .numero_ordine		= 1,
      .tipo			= ACQUISTO,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 50.00,
    },
    {
      .numero_ordine		= 2,
      .tipo			= VENDITA,
      .data_operazione		= NULL,
      .numero_quote		= 100,
      .prezzo_medio_eseguito	= 48.00,
    }
  };
  saldo_t	S[NUMERO_OPERAZIONI];

  printf("\n* Metodo delle medie ponderate: esempio di perdita 2\n\n");
  calcolo_storico(NUMERO_OPERAZIONI, O, S);
}

/* end of file */
