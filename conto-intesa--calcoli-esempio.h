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

#ifndef CONTO_INTESA__CALCOLI_ESEMPIO_H
#define CONTO_INTESA__CALCOLI_ESEMPIO_H 1


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

double
calcolo_rendimento_percentuale (double out, double in)
{
  return (100 * (out - in) / in);
}


/** --------------------------------------------------------------------
 ** Type definitions: saldo dopo compravendita.
 ** ----------------------------------------------------------------- */

typedef struct saldo_t		saldo_t;

struct saldo_t {
  double	numero_quote;
  double	prezzo_medio_carico;
  double	prezzo_medio_effettivo;
  double	controvalore_carico;
};

saldo_t const saldo_precedente_convenzionale = {
  .numero_quote			= 0.0,
  .prezzo_medio_carico		= 0.0,
  .prezzo_medio_effettivo	= 0.0,
  .controvalore_carico		= 0.0
};

void
saldo_print_ascii (saldo_t const * const S, char const * const descrizione)
{
  printf("-- %s\n\n", descrizione);
  printf("%-40s= %10.0f\n",	"numero quote",			S->numero_quote);
  printf("%-40s= %10.2f EUR\n", "prezzo medio carico",		S->prezzo_medio_carico);
  printf("%-40s= %10.2f EUR\n", "prezzo medio effettivo",	S->prezzo_medio_effettivo);
  printf("%-40s= %10.2f EUR\n", "controvalore di carico",	S->controvalore_carico);
  printf("\n");
  fflush(stdout);
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
  printf("%-40s= %10.0f\n",	"numero quote",			O->numero_quote);
  printf("%-40s= %10.2f EUR\n", "prezzo medio eseguito",	O->prezzo_medio_eseguito);
  printf("%-40s= %10.2f EUR\n", "controvalore dell'operazione",	O->controvalore_operazione);
  printf("%-40s= %10.2f EUR\n", "costo dell'operazione",	O->costo_operazione);
  printf("%-40s= %10.2f EUR\n", "controvalore totale",		O->controvalore_totale);
  printf("%-40s= %10.2f EUR\n", "prezzo medio di carico",	O->prezzo_medio_carico);
  printf("\n");
}

void
saldo_acquisto_init (saldo_t * const S, char const * descrizione,
		     operazione_acquisto_t const * const O,
		     saldo_t const * const S_precedente)
{
  S->numero_quote		= O->numero_quote + S_precedente->numero_quote;
  S->prezzo_medio_carico	= media_ponderata_2(O->numero_quote, O->prezzo_medio_carico,
						    S_precedente->numero_quote, S_precedente->prezzo_medio_carico);
  S->prezzo_medio_effettivo	= media_ponderata_2(O->numero_quote, O->prezzo_medio_eseguito,
						    S_precedente->numero_quote, S_precedente->prezzo_medio_effettivo);
  S->controvalore_carico	= S->numero_quote * S->prezzo_medio_carico;

  saldo_print_ascii(S, descrizione);
}


/** --------------------------------------------------------------------
 ** Type definitions: operazione vendita.
 ** ----------------------------------------------------------------- */

typedef struct operazione_vendita_t	operazione_vendita_t;

struct operazione_vendita_t {
  double	numero_quote;
  double	prezzo_medio_eseguito;
  double	controvalore_operazione;
  double	reddito_da_capitale;
  double	tasse_sul_reddito;
  double	costo_operazione;
  double	controvalore_totale;
  double	prezzo_medio_netto;
};

void
operazione_vendita_init (operazione_vendita_t * const O, char const * descrizione,
			 double const numero_quote, double const prezzo_medio_eseguito,
			 saldo_t const * const S_precedente)
{
  double	costo_medio_operazioni_acquisto, redditi_diversi;
  double	rendimento_percentuale, rendimento_in_valuta, utile_perdita_percentuale;

  O->numero_quote		= numero_quote;
  O->prezzo_medio_eseguito	= prezzo_medio_eseguito;
  O->controvalore_operazione	= O->numero_quote * O->prezzo_medio_eseguito;
  O->reddito_da_capitale	= O->numero_quote * (O->prezzo_medio_eseguito - S_precedente->prezzo_medio_effettivo);
  O->tasse_sul_reddito		= (O->reddito_da_capitale > 0.0)? (0.26 * O->reddito_da_capitale) : 0.0;
  O->costo_operazione		= 0.50 + 2.50 + 0.0024 * O->controvalore_operazione;
  O->controvalore_totale	= O->controvalore_operazione - O->costo_operazione - O->tasse_sul_reddito;
  O->prezzo_medio_netto		= O->controvalore_totale / O->numero_quote;

  costo_medio_operazioni_acquisto = O->numero_quote * (S_precedente->prezzo_medio_carico - S_precedente->prezzo_medio_effettivo);
  redditi_diversi = (O->reddito_da_capitale - (costo_medio_operazioni_acquisto + O->costo_operazione)) - O->reddito_da_capitale;

  utile_perdita_percentuale	= 100 * (O->prezzo_medio_eseguito - S_precedente->prezzo_medio_carico) / S_precedente->prezzo_medio_carico;
  rendimento_percentuale	= 100 * (O->prezzo_medio_netto - S_precedente->prezzo_medio_carico) / S_precedente->prezzo_medio_carico;
  rendimento_in_valuta		= O->numero_quote * (O->prezzo_medio_netto - S_precedente->prezzo_medio_carico);

  printf("-- %s\n\n", descrizione);
  printf("%-40s= %10.0f\n",	"numero quote",				O->numero_quote);
  printf("%-40s= %10.2f EUR\n", "prezzo medio eseguito",		O->prezzo_medio_eseguito);
  printf("%-40s= %10.2f EUR\n", "controvalore dell'operazione",		O->controvalore_operazione);
  printf("%-40s= %10.2f EUR\n", "reddito da capitale",			O->reddito_da_capitale);
  printf("%-40s= %10.2f EUR\n", "tasse sul reddito",			O->tasse_sul_reddito);
  printf("%-40s= %10.2f EUR\n", "costo dell'operazione di vendita",	O->costo_operazione);
  printf("%-40s= %10.2f EUR\n", "costo medio operazioni acquisto",	costo_medio_operazioni_acquisto);
  printf("%-40s= %10.2f EUR\n", "redditi diversi",			redditi_diversi);
  printf("%-40s= %10.2f EUR\n", "controvalore totale",			O->controvalore_totale);
  printf("%-40s= %10.2f EUR\n", "prezzo medio netto",			O->prezzo_medio_netto);
  printf("%-40s= %12.4f%%\n",	"Utile/Perdita percentuale",		utile_perdita_percentuale);
  printf("%-40s= %12.4f%%\n",	"rendimento percentuale",		rendimento_percentuale);
  printf("%-40s= %10.2f EUR\n",	"rendimento in valuta",			rendimento_in_valuta);
  printf("\n");
}

void
saldo_vendita_init (saldo_t * const S, char const * descrizione,
		    operazione_vendita_t const * const O,
		    saldo_t const * const S_precedente)
{
  S->numero_quote		= S_precedente->numero_quote - O->numero_quote;
  if (S->numero_quote > 0) {
    S->prezzo_medio_carico	= S_precedente->prezzo_medio_carico;
    S->prezzo_medio_effettivo	= S_precedente->prezzo_medio_effettivo;
    S->controvalore_carico	= S->numero_quote * S->prezzo_medio_carico;
  } else {
    S->prezzo_medio_carico	= 0.0;
    S->prezzo_medio_effettivo	= 0.0;
    S->controvalore_carico	= 0.0;
  }

  saldo_print_ascii(S, descrizione);
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#endif /* CONTO_INTESA__CALCOLI_ESEMPIO_H */

/* end of file */
