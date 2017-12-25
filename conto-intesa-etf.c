/* conto-intesa-etf.c -*- coding: utf-8-unix -*-
 *
 * Part of: MMUX Personal Finance
 * Contents: codice per il calcolo del prezzo medio di carico
 * Date: Dec 20, 2017
 *
 * Abstract
 *
 *
 *
 * Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>
 *
 * This program is free software:  you can redistribute it and/or modify
 * it under the terms of the  GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is  distributed in the hope that it  will be useful, but
 * WITHOUT  ANY   WARRANTY;  without   even  the  implied   warranty  of
 * MERCHANTABILITY or  FITNESS FOR  A PARTICULAR  PURPOSE.  See  the GNU
 * General Public License for more details.
 *
 * You should  have received a  copy of  the GNU General  Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "conto-intesa-etf.h"

saldo_t static const saldo_precedente_convenzionale_stru = {
  .numero_ordine			= 0,
  .data_saldo				= "0 gennaio 0",
  .numero_quote				= 0.0,
  .nav_prezzo_medio_carico		= 0.0,
  .prezzo_medio_carico			= 0.0,
  .controvalore_totale_carico		= 0.0
};

saldo_t const * const saldo_precedente_convenzionale = &saldo_precedente_convenzionale_stru;

static double	compravendita_controvalore_operazione	(compravendita_t const * O);
static double	compravendita_costo_operazione		(compravendita_t const * O);
static double	compravendita_tasse_reddito_capitale	(compravendita_t const * O, saldo_t const * S_precedente);
static double	compravendita_controvalore_totale	(compravendita_t const * O);
static double	compravendita_prezzo_medio_carico	(compravendita_t const * O);
static double	compravendita_prezzo_medio_netto	(compravendita_t const * O);
static double	compravendita_rendimento_percentuale	(compravendita_t const * O, saldo_t const * S_precedente);
static double	compravendita_rendimento_in_valuta	(compravendita_t const * O);

static void saldo_aggiorna_numero_quote			(saldo_t * S, compravendita_t const * O, saldo_t const * S_precedente);
static void saldo_aggiorna_nav_prezzo_medio_carico	(saldo_t * S, compravendita_t const * O, saldo_t const * S_precedente);
static void saldo_aggiorna_prezzo_medio_carico		(saldo_t * S, compravendita_t const * O, saldo_t const * S_precedente);
static void saldo_aggiorna_controvalore_totale_carico	(saldo_t * S);


/** --------------------------------------------------------------------
 ** Routines.
 ** ----------------------------------------------------------------- */

static double
media_ponderata (double peso_1, double valore_1, double peso_2, double valore_2)
{
  return (peso_1 * valore_1 + peso_2 * valore_2) / (peso_1 + peso_2);
}


/** --------------------------------------------------------------------
 ** Metodi per "compravendita_t".
 ** ----------------------------------------------------------------- */

void
compravendita_init (compravendita_t * O, saldo_t const * S_precedente)
{
  if (compravendita_is_acquisto(O)) {
    O->controvalore_operazione		= compravendita_controvalore_operazione(O);
    O->costo_operazione			= compravendita_costo_operazione(O);
    O->tasse_reddito_da_capitale	= nan("");
    O->controvalore_totale		= compravendita_controvalore_totale(O);
    O->prezzo_medio_carico		= compravendita_prezzo_medio_carico(O);
    O->prezzo_medio_netto		= nan("");
    O->rendimento_percentuale		= nan("");
    O->rendimento_in_valuta		= nan("");
  } else {
    O->controvalore_operazione		= compravendita_controvalore_operazione(O);
    O->costo_operazione			= compravendita_costo_operazione(O);
    O->tasse_reddito_da_capitale	= compravendita_tasse_reddito_capitale(O, S_precedente);
    O->controvalore_totale		= compravendita_controvalore_totale(O);
    O->prezzo_medio_carico		= nan("");
    O->prezzo_medio_netto		= compravendita_prezzo_medio_netto(O);
    O->rendimento_percentuale		= compravendita_rendimento_percentuale(O, S_precedente);
    O->rendimento_in_valuta		= compravendita_rendimento_in_valuta(O);
  }
}

bool
compravendita_is_acquisto (compravendita_t const * const O)
/* Ritorna "true" se questa operazione è un acquisto; altrimenti ritorna
   "false". */
{
  return O->is_acquisto;
}

double
compravendita_controvalore_operazione (compravendita_t const * const O)
/* Calcola e  ritorna il controvalore  di questa operazione.   Un numero
   positivo. */
{
  return (O->numero_quote * O->prezzo_medio_eseguito);
}

double
compravendita_costo_operazione (compravendita_t const * const O)
/* Calcola  e  ritorna il  valore  di  costi  e commissioni  per  questa
   operazione.   La  formula di  calcolo  è  la  stessa per  acquisti  e
   vendite.  Il valore ritornato è sempre positivo. */
{
  return 0.50 + 2.50 + 0.0024 * O->controvalore_operazione;
}

double
compravendita_tasse_reddito_capitale (compravendita_t const * const O, saldo_t const * const S_precedente)
/* Calcola e  ritorna l'ammontare  delle tasse  sul reddito  da capitale
   dovute  per la  vendita  di quote  nell'operazione "O".   L'argomento
   S_precedente deve  essere il  saldo precedente all'operazione  O.  Si
   suppone che le tasse da pagare siano il 26% dell'imponibile. */
{
  if (false == compravendita_is_acquisto(O)) {
    double	imponibile_per_quota	= O->prezzo_medio_eseguito - S_precedente->nav_prezzo_medio_carico;
    double	imponibile		= imponibile_per_quota * O->numero_quote;
    double	tasse_sul_reddito	= imponibile * 0.26;

    return tasse_sul_reddito;
  } else {
    fprintf(stderr, "%s: errore: non si pagano tasse per l'acquisto\n", __func__);
    exit(EXIT_FAILURE);
  }
}

double
compravendita_controvalore_totale (compravendita_t const * const O)
/* Calcola e ritorna il controvalore totale di questa operazione. */
{
  if (compravendita_is_acquisto(O)) {
    return (O->controvalore_operazione + O->costo_operazione);
  } else {
    return (O->controvalore_operazione - O->costo_operazione - O->tasse_reddito_da_capitale);
  }
}

double
compravendita_prezzo_medio_carico (compravendita_t const * const O)
/* Significativo solo per le operazioni  di acquisto.  Calcola e ritorna
   il prezzo  medio di  carico di  ogni quota  per questa  operazione di
   acquisto:  è usato,  nel saldo,  per  aggiornare il  prezzo medio  di
   carico.  Deve avere lo stesso segno di "prezzo_medio_eseguito". */
{
  if (compravendita_is_acquisto(O)) {
    return (O->controvalore_totale / O->numero_quote);
  } else {
    fprintf(stderr, "%s: errore: una vendita non ha prezzo medio di carico\n", __func__);
    exit(EXIT_FAILURE);
  }
}

double
compravendita_prezzo_medio_netto (compravendita_t const * const O)
/* Significativo solo per  le operazioni di vendita.   Calcola e ritorna
   il prezzo medio netto di ogni quota per questa operazione di vendita:
   è usato  per determinare  il guadagno di  una operazione  di vendita.
   Deve avere lo stesso segno di "prezzo_medio_eseguito". */
{
  if (false == compravendita_is_acquisto(O)) {
    return (O->controvalore_totale / O->numero_quote);
  } else {
    fprintf(stderr, "%s: errore: un acquisto non ha prezzo medio netto di vendita\n", __func__);
    exit(EXIT_FAILURE);
  }
}

double
compravendita_rendimento_percentuale (compravendita_t const * const O, saldo_t const * const S_precedente)
{
  return (100.0 * ((O->prezzo_medio_netto - S_precedente->prezzo_medio_carico) / S_precedente->prezzo_medio_carico));
}

double
compravendita_rendimento_in_valuta (compravendita_t const * const O)
{
  return (O->numero_quote * O->rendimento_percentuale);
}

void
compravendita_print_ascii (compravendita_t const * const O)
{
  printf("\nCompravendita %u, %s quote il %s:\n",
	 O->numero_ordine, (compravendita_is_acquisto(O)? "acquisto" : "vendita"), O->data_esecuzione);
  printf("\t%-40s = %10.2f\n",		"numero quote",			O->numero_quote);
  printf("\t%-40s = %+10.2f EUR\n",	"prezzo medio eseguito",	O->prezzo_medio_eseguito);
  printf("\t%-40s = %+10.2f EUR\n",	"controvalore operazione",	O->controvalore_operazione);
  printf("\t%-40s = %+10.2f EUR\n",	"costi e commissioni",		O->costo_operazione);

  if (false == compravendita_is_acquisto(O)) {
    printf("\t%-40s = %+10.2f EUR\n",	"tasse reddito da capitale",	O->tasse_reddito_da_capitale);
  }

  printf("\t%-40s = %+10.2f EUR\n",	"controvalore totale",		O->controvalore_totale);

  if (compravendita_is_acquisto(O)) {
    printf("\t%-40s = %+10.2f EUR\n",	"prezzo medio di carico di acquisto",	O->prezzo_medio_carico);
  } else {
    printf("\t%-40s = %+10.2f EUR\n",	"prezzo medio netto di vendita",	O->prezzo_medio_netto);
  }

  if (false == compravendita_is_acquisto(O)) {
    printf("\t%-40s = %+10.2f%%\n",	"rendimento percentuale della vendita",	O->rendimento_percentuale);
    printf("\t%-40s = %+10.2f EUR\n",	"rendimento in valuta della vendita",	O->rendimento_in_valuta);
  }
}


/** --------------------------------------------------------------------
 ** Metodi per "saldo_t".
 ** ----------------------------------------------------------------- */

void
saldo_init (saldo_t * const S, compravendita_t const * const O, saldo_t const * const S_precedente)
/* Inizializza il saldo  S con i dati della compravendita  O e del saldo
   precedente S_precedente. */
{
  S->numero_ordine	= O->numero_ordine;
  S->data_saldo				= O->data_esecuzione;
  saldo_aggiorna_numero_quote(S, O, S_precedente);
  saldo_aggiorna_nav_prezzo_medio_carico(S, O, S_precedente);
  saldo_aggiorna_prezzo_medio_carico(S, O, S_precedente);
  saldo_aggiorna_controvalore_totale_carico(S);
}

void
saldo_aggiorna_numero_quote (saldo_t * const S, compravendita_t const * const O, saldo_t const * const S_precedente)
{
  if (compravendita_is_acquisto(O)) {
    S->numero_quote	= S_precedente->numero_quote + O->numero_quote;
  } else {
    S->numero_quote	= S_precedente->numero_quote - O->numero_quote;
  }
}

void
saldo_aggiorna_nav_prezzo_medio_carico (saldo_t * const S, compravendita_t const * const O, saldo_t const * const S_precedente)
/* Il NAV  del prezzo medio  di carico è  la media ponderata  dei prezzi
   medi eseguiti per tutti gli acquisti. */
{
  if (compravendita_is_acquisto(O)) {
    /* Dopo un  acquisto: il NAV del  prezzo medio di carico  è la media
     * ponderata tra:
     *
     * - il prezzo medio eseguito del nuovo acquisto;
     *
     * - il precedente il NAV del  prezzo medio di carico.
     */
    S->nav_prezzo_medio_carico	= media_ponderata(O->numero_quote, O->prezzo_medio_eseguito,
						  S_precedente->numero_quote, S_precedente->nav_prezzo_medio_carico);
  } else {
    /* Dopo una vendita: il NAV del prezzo medio di carico è invariato. */
    S->nav_prezzo_medio_carico	= S_precedente->nav_prezzo_medio_carico;
  }
}

void
saldo_aggiorna_prezzo_medio_carico (saldo_t * const S, compravendita_t const * const O, saldo_t const * const S_precedente)
/* Il prezzo medio  di carico nel saldo è la  media ponderata dei prezzi
   medi di carico per tutti gli acquisti. */
{
  if (compravendita_is_acquisto(O)) {
    /* Dopo un acquisto: il prezzo medio  di carico nel saldo è la media
     * ponderata tra:
     *
     * - il prezzo medio di carico del nuovo acquisto;
     *
     * - il precedente il prezzo medio di carico nel saldo.
     */
    S->prezzo_medio_carico	= media_ponderata(O->numero_quote, compravendita_prezzo_medio_carico(O),
						  S_precedente->numero_quote, S_precedente->prezzo_medio_carico);
  } else {
    /* Dopo una vendita: il prezzo medio di carico è invariato. */
    S->prezzo_medio_carico	= S_precedente->prezzo_medio_carico;
  }
}

void
saldo_aggiorna_controvalore_totale_carico (saldo_t * const S)
/* Calcola e  ritorna il  controvalore totale  di carico.   Prodotto tra
   numero quote in carico e prezzo medio di carico fiscale. */
{
  S->controvalore_totale_carico = (S->numero_quote * S->prezzo_medio_carico);
}

void
saldo_print_ascii (saldo_t const * const S)
{
  printf("\nSaldo dopo la compravendita %u al %s:\n", S->numero_ordine, S->data_saldo);
  printf("\t%-40s = %10.2f\n",		"totale numero quote in carico",		S->numero_quote);
  printf("\t%-40s = %+12.4f EUR\n",	"prezzo medio di carico totale",		S->prezzo_medio_carico);
  printf("\t%-40s = %+12.4f EUR\n",	"NAV del prezzo medio di carico totale",	S->nav_prezzo_medio_carico);
  printf("\t%-40s = %+12.4f EUR\n",	"controvalore totale di carico",		S->controvalore_totale_carico);
}


/** --------------------------------------------------------------------
 ** Metodi per "nota_eseguito_t".
 ** ----------------------------------------------------------------- */

static bool
compare_double (double A, double B)
{
  return ((fabs(A - B) < 0.01)? true : false);
}

bool
nota_eseguito_confronto (nota_eseguito_t const * N, compravendita_t const * O, saldo_t const * S)
{
  if (N->numero_ordine != O->numero_ordine) {
    fprintf(stderr, "%s: nota %u, differenti numeri d'ordine tra nota (%u) e compravendita (%u)\n",
	    __func__, N->numero_ordine,
	    N->numero_ordine, O->numero_ordine);
    return false;
  }

  if (N->numero_ordine != S->numero_ordine) {
    fprintf(stderr, "%s: nota %u, differenti numeri d'ordine tra nota (%u) e saldo (%u)\n",
	    __func__, N->numero_ordine,
	    N->numero_ordine, S->numero_ordine);
    return false;
  }

  if (N->is_acquisto != O->is_acquisto) {
    fprintf(stderr, "%s: nota %u, la nota è di %s, mentre la compravendita è %s\n",
	    __func__, N->numero_ordine,
	    (N->is_acquisto)? "un acquisto" : "una vendita",
	    (O->is_acquisto)? "un acquisto" : "una vendita");
    return false;
  }

  if (N->numero_quote != O->numero_quote) {
    fprintf(stderr, "%s: nota %u, differenti numeri di quote tra nota (%.0f) e compravendita (%.0f)\n",
	    __func__, N->numero_ordine,
	    N->numero_quote, O->numero_quote);
    return false;
  }

  if (N->prezzo_medio_eseguito != O->prezzo_medio_eseguito) {
    fprintf(stderr, "%s: nota %u, differenti prezzi medi eseguiti tra nota (%.4f) e compravendita (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->prezzo_medio_eseguito, O->prezzo_medio_eseguito);
    return false;
  }

  if (! compare_double(N->controvalore_operazione, O->controvalore_operazione)) {
    fprintf(stderr, "%s: nota %u, differenti controvalori operazione tra nota (%.4f) e compravendita (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->controvalore_operazione, O->controvalore_operazione);
    return false;
  }

  if (! compare_double(N->costo_operazione, O->costo_operazione)) {
    fprintf(stderr, "%s: nota %u, differenti costi operazione tra nota (%.4f) e compravendita (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->costo_operazione, O->costo_operazione);
  }

  if (false == N->is_acquisto) {
    if (! compare_double(N->tasse_reddito_da_capitale, O->tasse_reddito_da_capitale)) {
      fprintf(stderr, "%s: nota %u, differenti tasse sul reddito tra nota (%.4f) e compravendita (%.4f)\n",
	      __func__, N->numero_ordine,
	      N->tasse_reddito_da_capitale, O->tasse_reddito_da_capitale);
      return false;
    }
  }

  if (! compare_double(N->controvalore_totale, O->controvalore_totale)) {
    fprintf(stderr, "%s: nota %u, differenti controvalori totali tra nota (%.4f) e compravendita (%.4f)\n",
	    __func__, N->numero_ordine,
	    N->controvalore_totale, O->controvalore_totale);
    return false;
  }

  if (false == N->is_acquisto) {
    if (! compare_double(N->nav_prezzo_medio_carico, S->nav_prezzo_medio_carico)) {
      fprintf(stderr, "%s: nota %u, differenti NAV del prezzo medio di carico tra nota (%.4f) e saldo (%.4f)\n",
	      __func__, N->numero_ordine,
	      N->nav_prezzo_medio_carico, S->nav_prezzo_medio_carico);
      return false;
    }
  }

  printf("Corretto confronto fra nota di eseguito %u, compravendita e saldo.\n", N->numero_ordine);
  return true;
}

/* end of file */
