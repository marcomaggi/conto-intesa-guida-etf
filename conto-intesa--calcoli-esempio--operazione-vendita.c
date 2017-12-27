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


/** --------------------------------------------------------------------
 ** Main.
 ** ----------------------------------------------------------------- */

int
main (void)
{
  operazione_acquisto_t		acquisto;
  saldo_t			saldo_iniziale;
  operazione_vendita_t		vendita;
  saldo_t			saldo_vendita;

  double	numero_quote;
  double	prezzo_medio_eseguito;

  printf("\n*** Calcoli per gli esempi nella guida: sezione \"Descrizione di un'operazione di vendita\"\n\n");

  operazione_acquisto_init(&acquisto, "Operazione acquisto preliminare", 100.0, 100.00);
  saldo_acquisto_init(&saldo_iniziale, "Saldo iniziale", &acquisto, &saldo_precedente_convenzionale);

  /* Calcolo  del  prezzo_medio_eseguido:   media  ponderata  prezzi  di
     vendita in piú fasi. */
  {
    double	numero_quote_fase_1	= 20.0;
    double	numero_quote_fase_2	= 30.0;
    double	numero_quote_fase_3	= 40.0;
    double	prezzo_fase_1		= 102.0;
    double	prezzo_fase_2		= 103.0;
    double	prezzo_fase_3		= 104.0;

    numero_quote = numero_quote_fase_1 + numero_quote_fase_2 + numero_quote_fase_3;
    prezzo_medio_eseguito = media_ponderata_3(numero_quote_fase_1, prezzo_fase_1,
					      numero_quote_fase_2, prezzo_fase_2,
					      numero_quote_fase_3, prezzo_fase_3);
  }

  operazione_vendita_init(&vendita, "Operazione vendita", numero_quote, prezzo_medio_eseguito, &saldo_iniziale);
  saldo_vendita_init(&saldo_vendita, "Saldo dopo l'operazione", &vendita, &saldo_iniziale);

  fflush(stdout);
  exit(EXIT_SUCCESS);
}

/* end of file */
