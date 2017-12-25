/* conto-intesa-esempio-1.c -*- coding: utf-8-unix -*-

   Part of: MMUX Personal Finance
   Contents: calcoli di esempio
   Date: Sun Dec 24, 2017

   Abstract



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

#include "conto-intesa-etf.h"


/** --------------------------------------------------------------------
 ** Tabella operazioni.
 ** ----------------------------------------------------------------- */

#define NUMERO_COMPRAVENDITE	6
compravendita_t	compravendite_abcd[NUMERO_COMPRAVENDITE] = {
  {
    .numero_ordine			= 1,
    .data_esecuzione			= "3001 gennaio 01",
    .is_acquisto			= true,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= 47.46,
  },
  {
    .numero_ordine			= 2,
    .data_esecuzione			= "3001 febbraio 02",
    .is_acquisto			= true,
    .numero_quote			= 70.0 + 35.0,
    .prezzo_medio_eseguito		= 47.10,
  },
  {
    .numero_ordine			= 3,
    .data_esecuzione			= "3001 marzo 03",
    .is_acquisto			= true,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= 47.30,
  },
  {
    .numero_ordine			= 4,
    .data_esecuzione			= "3001 aprile 04",
    .is_acquisto			= true,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= 47.935,
  },
  {
    .numero_ordine			= 5,
    .data_esecuzione			= "3001 maggio 05",
    .is_acquisto			= false,
    .numero_quote			= 210.0,
    .prezzo_medio_eseguito		= 50.18,
  },
  {
    .numero_ordine			= 6,
    .data_esecuzione			= "3001 giugno 06",
    .is_acquisto			= false,
    .numero_quote			= 105,
    .prezzo_medio_eseguito		= 50.13,
  },
};


/** --------------------------------------------------------------------
 ** Tabella note di ordine eseguito.
 ** ----------------------------------------------------------------- */

nota_eseguito_t	note_abcd[NUMERO_COMPRAVENDITE] = {
  {
    .numero_ordine			= 1,
    .data_esecuzione			= "3001 gennaio 01",
    .is_acquisto			= true,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= +47.46,
    .controvalore_operazione		= +4983.30,
    .costo_operazione			= 0.50 + 2.50 + 11.96,
    .tasse_reddito_da_capitale		= nan(""),
    .controvalore_totale		= +4998.26,
    .nav_prezzo_medio_carico		= nan(""),
  },
  {
    .numero_ordine			= 2,
    .data_esecuzione			= "3001 febbraio 02",
    .is_acquisto			= true,
    .numero_quote			= 70.0 + 35.0,
    .prezzo_medio_eseguito		= +47.10,
    .controvalore_operazione		= 1648.50 + 3297.00,
    .costo_operazione			= 0.50 + 2.50 + 3.96 + 7.91,
    .tasse_reddito_da_capitale		= nan(""),
    .controvalore_totale		= 1655.46 + 3304.91,
    .nav_prezzo_medio_carico		= nan(""),
  },
  {
    .numero_ordine			= 3,
    .data_esecuzione			= "3001 marzo 03",
    .is_acquisto			= true,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= 47.30,
    .controvalore_operazione		= 4966.50,
    .costo_operazione			= 0.50 + 2.50 + 11.92,
    .tasse_reddito_da_capitale		= nan(""),
    .controvalore_totale		= 4981.42,
    .nav_prezzo_medio_carico		= nan(""),

  },
  {
    .numero_ordine			= 4,
    .data_esecuzione			= "3001 aprile 04",
    .is_acquisto			= true,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= 47.935,
    .controvalore_operazione		= 5033.18,
    .costo_operazione			= 0.50 + 2.50 + 12.08,
    .tasse_reddito_da_capitale		= nan(""),
    .controvalore_totale		= 5048.26,
    .nav_prezzo_medio_carico		= nan(""),
  },
  {
    .numero_ordine			= 5,
    .data_esecuzione			= "3001 maggio 05",
    .is_acquisto			= false,
    .numero_quote			= 210.0,
    .prezzo_medio_eseguito		= 50.18,
    .controvalore_operazione		= 10537.80,
    .costo_operazione			= 0.50 + 2.50 + 25.29,
    .tasse_reddito_da_capitale		= 149.13,
    .controvalore_totale		= 10360.38,
    .nav_prezzo_medio_carico		= 47.4487,
  },
  {
    .numero_ordine			= 6,
    .data_esecuzione			= "3001 giugno 06",
    .is_acquisto			= false,
    .numero_quote			= 105.0,
    .prezzo_medio_eseguito		= 50.13,
    .controvalore_operazione		= 5263.65,
    .costo_operazione			= 0.50 + 2.50 + 12.63,
    .tasse_reddito_da_capitale		= 73.20,
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
  saldo_t	saldo_abcd[NUMERO_COMPRAVENDITE];

  printf("\n*** Conto Intesa Sanpaolo, operazioni di compravendita ETF ABCD (esempio 1).\n\n");

  /* Inizializzazione. */
  compravendita_init(&(compravendite_abcd[0]), saldo_precedente_convenzionale);
  saldo_init(&(saldo_abcd[0]), &(compravendite_abcd[0]), saldo_precedente_convenzionale);
  for (unsigned i=1; i<NUMERO_COMPRAVENDITE; ++i) {
    compravendita_init(&(compravendite_abcd[i]), &(saldo_abcd[i-1]));
    saldo_init(&(saldo_abcd[i]), &(compravendite_abcd[i]), &(saldo_abcd[i-1]));
  }

  /* Stampa risultati. */
  for (int i=0; i<NUMERO_COMPRAVENDITE; ++i) {
    compravendita_print_ascii(&(compravendite_abcd[i]));
    saldo_print_ascii(&(saldo_abcd[i]));
  }
  fflush(stdout);

  printf("\n");

  /* Confronto con le note di eseguito. */
  for (int i=0; i<NUMERO_COMPRAVENDITE; ++i) {
    nota_eseguito_confronto(&(note_abcd[i]), &(compravendite_abcd[i]), &(saldo_abcd[i]));
  }
  fflush(stdout);

  exit(EXIT_SUCCESS);
}

/* end of file */
