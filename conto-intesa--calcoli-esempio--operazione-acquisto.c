/* conto-intesa--calcoli-esempio--operazione-acquisto.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Dec 27, 2017

   Abstract

	Calcoli di esempio  nella guida, per la  sezione "Descrizione di
	un'operazione di acquisto".

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
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  double	numero_quote_fase_1	= 20.0;
  double	numero_quote_fase_2	= 30.0;
  double	numero_quote_fase_3	= 40.0;
  double	numero_quote		= numero_quote_fase_1 + numero_quote_fase_2 + numero_quote_fase_3;
  double	prezzo_medio_eseguito;
  double	controvalore_operazione;
  double	costo_operazione;
  double	controvalore_totale;
  double	prezzo_medio_carico;

  printf("\n*** Calcoli per gli esempi nella guida: sezione \"Descrizione di un'operazione di acquisto\"\n\n");

  /* Calcolo  del  prezzo_medio_eseguido:   media  ponderata  prezzi  di
     acquisto in piú fasi. */
  {
    double	prezzo_fase_1		= 22.0;
    double	prezzo_fase_2		= 33.0;
    double	prezzo_fase_3		= 44.0;

    prezzo_medio_eseguito = media_ponderata_3(numero_quote_fase_1, prezzo_fase_1,
					      numero_quote_fase_2, prezzo_fase_2,
					      numero_quote_fase_3, prezzo_fase_3);
    printf("%-30s= %10.2f EUR\n", "prezzo medio eseguito", prezzo_medio_eseguito);
  }

  /* Calcolo del controvalore dell'operazione. */
  {
    controvalore_operazione = numero_quote * prezzo_medio_eseguito;
    printf("%-30s= %10.2f EUR\n", "controvalore dell'operazione", controvalore_operazione);
  }

  /* Calcolo del costo dell'operazione. */
  {
    costo_operazione = 0.50 + 2.50 + 0.0024 * controvalore_operazione;
    printf("%-30s= %10.2f EUR\n", "costo dell'operazione", costo_operazione);
  }

  /* Calcolo del controvalore totale dell'operazione. */
  {
    controvalore_totale = controvalore_operazione + costo_operazione;
    printf("%-30s= %10.2f EUR\n", "controvalore totale", controvalore_totale);
  }

  /* Calcolo del prezzo medio di carico dell'operazione. */
  {
    prezzo_medio_carico = controvalore_totale / numero_quote;
    printf("%-30s= %10.2f EUR\n", "prezzo medio di carico", prezzo_medio_carico);
  }

  fflush(stdout);
  exit(EXIT_SUCCESS);
}

/* end of file */
