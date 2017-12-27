/* conto-intesa--calcoli-esempio--saldo-acquisto.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di  esempio nella  guida, per la  sezione "Aggiornamento
	del saldo dopo un'operazione di acquisto".

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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/** --------------------------------------------------------------------
 ** Helpers.
 ** ----------------------------------------------------------------- */

double
media_ponderata_2 (double peso_1, double valore_1, double peso_2, double valore_2)
{
  return (peso_1 * valore_1 + peso_2 * valore_2) / (peso_1 + peso_2);
}

double
media_ponderata_3 (double peso_1, double valore_1,
		   double peso_2, double valore_2,
		   double peso_3, double valore_3)
{
  return (peso_1 * valore_1 + peso_2 * valore_2 + peso_3 * valore_3) / (peso_1 + peso_2 + peso_3);
}


/** --------------------------------------------------------------------
 ** Type definitions: operazione acquisto.
 ** ----------------------------------------------------------------- */

typedef struct operazione_acquisto_t	operazione_acquisto_t;

struct operazione_acquisto_t {
  double	numero_quote;
  double	prezzo_medio_eseguito;
  double	controvalore_operazione;
  double	costo_operazione;
  double	controvalore_totale;
  double	prezzo_medio_carico;
};

void
operazione_acquisto_init (operazione_acquisto_t * const O, char const * descrizione,
			  double const numero_quote, double const prezzo_medio_eseguito)
{
  O->numero_quote		= numero_quote;
  O->prezzo_medio_eseguito	= prezzo_medio_eseguito;
  O->controvalore_operazione	= O->numero_quote * O->prezzo_medio_eseguito;
  O->costo_operazione		= 0.50 + 2.50 + 0.0024 * O->controvalore_operazione;
  O->controvalore_totale	= O->controvalore_operazione + O->costo_operazione;
  O->prezzo_medio_carico	= O->controvalore_totale / O->numero_quote;

  printf("-- %s\n\n", descrizione);
  printf("%-30s= %10.0f\n",	"numero quote",			O->numero_quote);
  printf("%-30s= %10.2f EUR\n", "prezzo medio eseguito",	O->prezzo_medio_eseguito);
  printf("%-30s= %10.2f EUR\n", "controvalore dell'operazione",	O->controvalore_operazione);
  printf("%-30s= %10.2f EUR\n", "costo dell'operazione",	O->costo_operazione);
  printf("%-30s= %10.2f EUR\n", "controvalore totale",		O->controvalore_totale);
  printf("%-30s= %10.2f EUR\n", "prezzo medio di carico",	O->prezzo_medio_carico);
  printf("\n");
}


/** --------------------------------------------------------------------
 ** Type definitions: operazione acquisto.
 ** ----------------------------------------------------------------- */

typedef struct saldo_acquisto_t	saldo_acquisto_t;

struct saldo_acquisto_t {
  double	numero_quote;
  double	prezzo_medio_carico;
  double	nav_prezzo_medio_carico;
  double	controvalore_carico;
};

void
saldo_acquisto_init (saldo_acquisto_t * const S, char const * descrizione,
		     operazione_acquisto_t const * const O,
		     saldo_acquisto_t const * const S_precedente)
{
  S->numero_quote		= O->numero_quote + S_precedente->numero_quote;
  S->prezzo_medio_carico	= media_ponderata_2(O->numero_quote, O->prezzo_medio_carico,
						    S_precedente->numero_quote, S_precedente->prezzo_medio_carico);
  S->nav_prezzo_medio_carico	= media_ponderata_2(O->numero_quote, O->prezzo_medio_eseguito,
						    S_precedente->numero_quote, S_precedente->nav_prezzo_medio_carico);
  S->controvalore_carico	= S->numero_quote * S->prezzo_medio_carico;

  printf("-- %s\n\n", descrizione);
  printf("%-30s= %10.0f\n",	"numero quote",			S->numero_quote);
  printf("%-30s= %10.2f EUR\n", "prezzo medio carico",		S->prezzo_medio_carico);
  printf("%-30s= %10.2f EUR\n", "NAV prezzo medio carico",	S->nav_prezzo_medio_carico);
  printf("%-30s= %10.2f EUR\n", "controvalore di carico",	S->controvalore_carico);
  printf("\n");
}

saldo_acquisto_t const saldo_precedente_convenzionale = {
  .numero_quote			= 0.0,
  .prezzo_medio_carico		= 0.0,
  .nav_prezzo_medio_carico	= 0.0,
  .controvalore_carico		= 0.0
};


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  double			numero_quote_1		= 100;
  double			numero_quote_2		= 200;
  double			numero_quote_3		= 300;
  double			prezzo_medio_eseguito_1	= 110.00;
  double			prezzo_medio_eseguito_2	= 120.00;
  double			prezzo_medio_eseguito_3	= 130.00;
  operazione_acquisto_t		acquisto_1;
  operazione_acquisto_t		acquisto_2;
  operazione_acquisto_t		acquisto_3;
  saldo_acquisto_t		saldo_1;
  saldo_acquisto_t		saldo_2;
  saldo_acquisto_t		saldo_3;

  printf("\n*** Calcoli  per gli esempi  nella guida: sezione  \"Aggiornamento del saldo dopo un'operazione di acquisto\"\n\n");

  operazione_acquisto_init(&acquisto_1, "Operazione acquisto 1", numero_quote_1, prezzo_medio_eseguito_1);
  operazione_acquisto_init(&acquisto_2, "Operazione acquisto 2", numero_quote_2, prezzo_medio_eseguito_2);
  operazione_acquisto_init(&acquisto_3, "Operazione acquisto 3", numero_quote_3, prezzo_medio_eseguito_3);

  saldo_acquisto_init (&saldo_1, "Saldo dopo l'operazione 1", &acquisto_1, &saldo_precedente_convenzionale);
  saldo_acquisto_init (&saldo_2, "Saldo dopo l'operazione 2", &acquisto_2, &saldo_1);
  saldo_acquisto_init (&saldo_3, "Saldo dopo l'operazione 3", &acquisto_3, &saldo_2);

  printf("\n-- Calcolo del totale dei costi\n");
  {
    double	costo_totale_1 = acquisto_1.costo_operazione + acquisto_2.costo_operazione + acquisto_3.costo_operazione;
    double	costo_totale_2 = saldo_3.numero_quote * (saldo_3.prezzo_medio_carico - saldo_3.nav_prezzo_medio_carico);

    printf("%-30s= %10.2f EUR\n", "come somma dei costi",	costo_totale_1);
    printf("%-30s= %10.2f EUR\n", "dai prezzi medi di carico",	costo_totale_2);
    printf("%-30s= %10.2f EUR\n", "costo medio per quota",	costo_totale_2 / saldo_3.numero_quote);
  }

  fflush(stdout);
  exit(EXIT_SUCCESS);
}

/* end of file */
