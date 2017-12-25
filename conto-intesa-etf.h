/* conto-intesa-etf.h -*- coding: utf-8-unix -*-
 *
 * Part of: MMUX Personal Finance
 * Contents: header file
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

#ifndef CONTO_INTESA_ETF_H
#define CONTO_INTESA_ETF_H 1


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The  macro  CCTEMPLATE_UNUSED  indicates  that a  function,  function
   argument or variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CONTO_INTESA_ETF_UNUSED;
   int foo (char unused_argument CONTO_INTESA_ETF_UNUSED);
   int unused_variable CONTO_INTESA_ETF_UNUSED;
*/
#ifdef __GNUC__
#  define CONTO_INTESA_ETF_UNUSED		__attribute__((__unused__))
#else
#  define CONTO_INTESA_ETF_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

/* I found  the following chunk on  the Net.  (Marco Maggi;  Sun Feb 26,
   2012) */
#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define conto_intesa_etf_decl		__attribute__((__dllexport__)) extern
#    else
#      define conto_intesa_etf_decl		__declspec(dllexport) extern
#    endif
#  else
#    ifdef __GNUC__
#      define conto_intesa_etf_decl		__attribute__((__dllimport__)) extern
#    else
#      define conto_intesa_etf_decl		__declspec(dllimport) extern
#    endif
#  endif
#  define conto_intesa_etf_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define conto_intesa_etf_decl		__attribute__((__visibility__("default"))) extern
#    define conto_intesa_etf_private_decl	__attribute__((__visibility__("hidden")))  extern
#  else
#    define conto_intesa_etf_decl		extern
#    define conto_intesa_etf_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>


/** --------------------------------------------------------------------
 ** Forward type definitions.
 ** ----------------------------------------------------------------- */

typedef struct compravendita_t		compravendita_t;
typedef struct nota_eseguito_t		nota_eseguito_t;
typedef struct saldo_t			saldo_t;


/** --------------------------------------------------------------------
 ** Type definition: compravendita.
 ** ----------------------------------------------------------------- */

/* La   struttura   "compravendita_t"   rappresenta   un'operazione   di
 * compravendita: acquisto o  vendita di quote di un  fondo.  Istanze di
 * questo tipo possono essere costruite come segue:
 *
 *    compravendita_t O1 = {
 *      .numero_ordine		= 1,
 *      .data_esecuzione	= "3001 gennaio 01",
 *      .is_acquisto		= true,
 *      .numero_quote		= 100,
 *      .prezzo_medio_eseguito	= 1000,00
 *    };
 *
 *    compravendita_t O2 = {
 *      .numero_ordine		= 2,
 *      .data_esecuzione	= "3001 febbraio 02",
 *      .is_acquisto		= false,
 *      .numero_quote		= 88,
 *      .prezzo_medio_eseguito	= 987,65
 *    };
 *
 * gli altri campi sono inizializzati dal costruttore.
 */
struct compravendita_t {
  /* Numero  d'ordine  dell'operazione:  1,  2,  3,  ...;  è  un  intero
     strettamente   positivo   che    identifica   univocamente   questa
     compravendita.  È obbligatorio  mantenere correttamente l'ordine in
     cui le compravendite sono eseguite. */
  unsigned		numero_ordine;

  /* Data  di esecuzione  della  compravendita titoli.   Una stringa  in
     formato  ASCIIZ  come  "3001  gennaio   01".   È  usata  solo  come
     descrizione nel rapporto prodotto dal programma. */
  char const *		data_esecuzione;

  /* Vero se questa operazione è un acquisto; falso se è una vendita. */
  bool			is_acquisto;

  /* Numero  quote  acquistate  o  vendute;  è  un  intero  strettamente
     positivo.  La rappresentazione come "double" è per comodità. */
  double		numero_quote;

  /* Prezzo medio di una singola  quota dell'ordine eseguito di acquisto
     o vendita. */
  double		prezzo_medio_eseguito;

  /* Controvalore dell'operazione.  Prodotto tra il numero di quote e il
     prezzo medio eseguito per ogni quota. */
  double		controvalore_operazione;

  /* Costo dell'operazione.   Costi, spese  e commissioni da  pagare per
     eseguire l'acquisto o la vendita. */
  double		costo_operazione;

  /* Tasse  da  pagare   sul  reddito  da  capitale.    Questo  campo  è
     significativo   solo  se   questa  istanza   è  una   vendita.   Se
     l'operazione  è  un'acquisto:  il  valore di  questo  campo  è  non
     specificato. */
  double		tasse_reddito_da_capitale;

  /* Controvalore totale dell'operazione.
   *
   * - Se  l'operazione  è  un'acquisto:  il controvalore  totale  è  la
   *   quantità di denaro che esce dal Conto Corrente ed entra nel Conto
   *   Titoli.   È pari  al  controvalore dell'operazione  piú il  costo
   *   dell'operazione.
   *
   * - Se  l'operazione  è una  vendita:  il  controvalore totale  è  la
   *   quantità di denaro  che esce dal Conto Titoli ed  entra nel Conto
   *   Corrente.  È  pari al controvalore dell'operazione  meno il costo
   *   dell'operazione, meno le tasse sul reddito da capitale.
   */
  double		controvalore_totale;

  /* Se  l'operazione è  un  acquisto: è  il  rapporto tra  controvalore
     totale  e  numero  di  quote acquistate.   Se  l'operazione  è  una
     vendita: il valore è non specificato. */
  double		prezzo_medio_carico;

  /* Se  l'operazione è  una  vendita: è  il  rapporto tra  controvalore
     totale e numero  di quote vendute.  Se l'operazione  è un acquisto:
     il valore è non specificato. */
  double		prezzo_medio_netto;

  /* Se l'operazione  è una vendita: rendimento  percentuale rispetto al
     prezzo  medio  di  carico  nel  saldo  prima  dell'operazione.   Se
     l'operazione è un acquisto: il valore è non specificato */
  double		rendimento_percentuale;

  /* Se l'operazione  è una  vendita: rendimento  in valuta  rispetto al
     prezzo  medio  di  carico  nel  saldo  prima  dell'operazione.   Se
     l'operazione è un acquisto: il valore è non specificato */
  double		rendimento_in_valuta;
};


/** --------------------------------------------------------------------
 ** Type definition: saldo.
 ** ----------------------------------------------------------------- */

/* Dopo  ogni   operazione  di   compravendita:  si  produce   un  saldo
   aggiornato.   A ogni  istanza  di  "compravendita_t" corrisponde  una
   istanza di "saldo_t". */
struct saldo_t {
  /* Numero  d'ordine  dell'operazione  di  compravendita  precedente  a
     questo  saldo:  0  1,  2,  3,  ...;  è  un  intero  che  identifica
     univocamente questo saldo.

     L'istanza  predefinita puntata  da "saldo_precedente_convenzionale"
     ha questo campo impostato a 0. */
  unsigned		numero_ordine;

  /* Data  di calcolo  del saldo.   È lo  stesso valore  dell'istanza di
     "compravendita_t" precedente a questo saldo. */
  char const *		data_saldo;

  /* Numero  quote  in  carico,  alla   data  del  saldo;  è  un  intero
     strettamente  positivo.  La  rappresentazione come  "double" è  per
     comodità. */
  double		numero_quote;

  /* NAV del prezzo medio di carico:  media ponderata dei prezzi medi di
     eseguito di  tutti gli acquisti  precedenti il saldo.  È  usato nel
     calcolo dell'imponibile su cui pagare le tasse sui redditi. */
  double		nav_prezzo_medio_carico;

  /* Prezzo medio  di ogni quota in  carico, alla data del  saldo.  È la
     media ponderata  dei prezzi  medi di carico  di tutti  gli acquisti
     precedenti il saldo. */
  double		prezzo_medio_carico;

  /* Prodotto tra  il numero  di quote  in carico e  il prezzo  medio di
     carico. */
  double		controvalore_totale_carico;
};


/** --------------------------------------------------------------------
 ** Type definition: nota di ordine eseguito.
 ** ----------------------------------------------------------------- */

/* Dopo ogni  operazione di  compravendita: nella sezione  documenti del
 * sito  di home  banking  è  disponibile una  "Nota  di eseguito",  che
 * riporta tutti i  dati dell'operazione.  È utile  confrontare i valori
 * calcolati  nella struttura  "compravendita_t"  con  i dati  riportati
 * nella nota.
 *
 * Una  nota   di  eseguito  per   un'ordine  di  acquisto   può  essere
 * inizializzata come:
 *
 *    nota_eseguito_t N = {
 *      .numero_ordine			= 1,
 *      .data_esecuzione		= "3001 gennaio 01",
 *      .is_acquisto			= true,
 *      .numero_quote			= 105.0,
 *      .prezzo_medio_eseguito		= +47.46,
 *      .controvalore_operazione	= +4983.30,
 *      .costo_operazione		= 0.50 + 2.50 + 11.96,
 *      .tasse_reddito_da_capitale	= nan(""),
 *      .controvalore_totale		= +4998.26,
 *      .nav_prezzo_medio_carico	= nan(""),
 *    };
 *
 * Una  nota   di  eseguito   per  un'ordine   di  vendita   può  essere
 * inizializzata come:
 *
 *    nota_eseguito_t N = {
 *      .numero_ordine			= 6,
 *      .data_esecuzione		= "3001 giugno 06",
 *      .is_acquisto			= false,
 *      .numero_quote			= 105.0,
 *      .prezzo_medio_eseguito		= 50.13,
 *      .controvalore_operazione	= 5263.65,
 *      .costo_operazione		= 0.50 + 2.50 + 12.63,
 *      .tasse_reddito_da_capitale	= 73.20,
 *      .controvalore_totale		= 5174.82,
 *      .nav_prezzo_medio_carico	= 47.4487,
 *   };
 */
struct nota_eseguito_t {
  /* Numero  d'ordine  dell'operazione:  1,  2,  3,  ...;  è  un  intero
     strettamente   positivo   che    identifica   univocamente   questa
     compravendita.  È obbligatorio  mantenere correttamente l'ordine in
     cui le compravendite sono eseguite. */
  unsigned		numero_ordine;

  /* Data  di esecuzione  della  compravendita titoli.   Una stringa  in
     formato  ASCIIZ  come  "3001  gennaio   01".   È  usata  solo  come
     descrizione nel rapporto prodotto dal programma. */
  char const *		data_esecuzione;

  /* Vero se questa operazione è un acquisto; falso se è una vendita. */
  bool			is_acquisto;

  /* Numero  quote  acquistate  o  vendute;  è  un  intero  strettamente
     positivo.  La rappresentazione come "double" è per comodità. */
  double		numero_quote;

  /* Prezzo medio di una singola  quota dell'ordine eseguito di acquisto
     o vendita. */
  double		prezzo_medio_eseguito;

  /* Controvalore dell'operazione.  Prodotto tra il numero di quote e il
     prezzo medio eseguito per ogni quota. */
  double		controvalore_operazione;

  /* Costo dell'operazione.   Costi, spese  e commissioni da  pagare per
     eseguire l'acquisto o la vendita. */
  double		costo_operazione;

  /* Se  l'operazione è  una vendita:  tasse  da pagare  sul reddito  da
     capitale.

     Se  l'operazione è  un'acquisto: il  valore di  questo campo  è non
     specificato e non è presente nelle note di eseguito. */
  double		tasse_reddito_da_capitale;

  /* Controvalore totale dell'operazione.
   *
   * - Se  l'operazione  è  un'acquisto:  il controvalore  totale  è  la
   *   quantità di denaro che esce dal Conto Corrente ed entra nel Conto
   *   Titoli.   È pari  al  controvalore dell'operazione  piú il  costo
   *   dell'operazione.
   *
   * - Se  l'operazione  è una  vendita:  il  controvalore totale  è  la
   *   quantità di denaro  che esce dal Conto Titoli ed  entra nel Conto
   *   Corrente.  È  pari al controvalore dell'operazione  meno il costo
   *   dell'operazione, meno le tasse sul reddito da capitale.
   */
  double		controvalore_totale;

  /* Se l'operazione è  una vendita: il NAV del prezzo  medio di carico:
     media ponderata dei  prezzi medi di eseguito di  tutti gli acquisti
     precedenti il  saldo; è  usato nel  calcolo dell'imponibile  su cui
     pagare le tasse sui redditi.

     Se l'operazione è un acquisto: il valore non è riportato nelle note
     di eseguito. */
  double		nav_prezzo_medio_carico;
};


/** --------------------------------------------------------------------
 ** Global definitions.
 ** ----------------------------------------------------------------- */

extern saldo_t const * const saldo_precedente_convenzionale;


/** --------------------------------------------------------------------
 ** Function prototypes.
 ** ----------------------------------------------------------------- */

extern void	compravendita_init			(compravendita_t * O, saldo_t const * S_precedente);

extern bool	compravendita_is_acquisto		(compravendita_t const * O);
extern void	compravendita_print_ascii		(compravendita_t const * O);

extern void	saldo_init				(saldo_t * S, compravendita_t const * O, saldo_t const * S_precedente);
extern void	saldo_print_ascii			(saldo_t const * S);

extern bool	nota_eseguito_confronto			(nota_eseguito_t const * N, compravendita_t const * O, saldo_t const * S);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CONTO_INTESA_ETF_H */

/* end of file */
