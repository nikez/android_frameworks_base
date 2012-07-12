/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
/*

 Filename: sbr_envelope_calc_tbl.c

------------------------------------------------------------------------------
 REVISION HISTORY


 Who:                                   Date: MM/DD/YYYY
 Description:

------------------------------------------------------------------------------
 INPUT AND OUTPUT DEFINITIONS



------------------------------------------------------------------------------
 FUNCTION DESCRIPTION


------------------------------------------------------------------------------
 REQUIREMENTS


------------------------------------------------------------------------------
 REFERENCES

SC 29 Software Copyright Licencing Disclaimer:

This software module was originally developed by
  Coding Technologies

and edited by
  -

in the course of development of the ISO/IEC 13818-7 and ISO/IEC 14496-3
standards for reference purposes and its performance may not have been
optimized. This software module is an implementation of one or more tools as
specified by the ISO/IEC 13818-7 and ISO/IEC 14496-3 standards.
ISO/IEC gives users free license to this software module or modifications
thereof for use in products claiming conformance to audiovisual and
image-coding related ITU Recommendations and/or ISO/IEC International
Standards. ISO/IEC gives users the same free license to this software module or
modifications thereof for research purposes and further ISO/IEC standardisation.
Those intending to use this software module in products are advised that its
use may infringe existing patents. ISO/IEC have no liability for use of this
software module or modifications thereof. Copyright is not released for
products that do not conform to audiovisual and image-coding related ITU
Recommendations and/or ISO/IEC International Standards.
The original developer retains full right to modify and use the code for its
own purpose, assign or donate the code to a third party and to inhibit third
parties from using the code for products that do not conform to audiovisual and
image-coding related ITU Recommendations and/or ISO/IEC International Standards.
This copyright notice must be included in all copies or derivative works.
Copyright (c) ISO/IEC 2002.

------------------------------------------------------------------------------
 PSEUDO-CODE

------------------------------------------------------------------------------
*/


/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/

#ifdef AAC_PLUS


#include    "sbr_envelope_calc_tbl.h"

/*----------------------------------------------------------------------------
; MACROS
; Define module specific macros here
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
; DEFINES
; Include all pre-processor statements here. Include conditional
; compile variables also.
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; LOCAL FUNCTION DEFINITIONS
; Function Prototype declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; LOCAL STORE/BUFFER/POINTER DEFINITIONS
; Variable declaration - defined here and used outside this module
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; EXTERNAL FUNCTION REFERENCES
; Declare functions defined elsewhere and referenced in this module
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; EXTERNAL GLOBAL STORE/BUFFER/POINTER REFERENCES
; Declare variables used in this module but defined elsewhere
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; FUNCTION CODE
----------------------------------------------------------------------------*/
#define Q30_fmt(x)   (Int32)(x*((Int32)1<<30) + (x>=0?0.5F:-0.5F))
#define Qfmt15(x)    (Int16)(x*((Int32)1<<15) + (x>=0?0.5F:-0.5F))


const Int32 limGains[5] = { Q30_fmt(0.70795f), Q30_fmt(1.0f),
                            Q30_fmt(1.41254f), Q30_fmt(1.16415321826935f), 33
                          };

const Int32 smoothLengths[2] = { 4, 0 };

const Int16 rP_LCx[512] =
{
    Qfmt15(-0.99948153278296f), Qfmt15(0.97113454393991f), Qfmt15(0.14130051758487f), Qfmt15(-0.47005496701697f),
    Qfmt15(0.80705063769351f), Qfmt15(-0.38981478896926f), Qfmt15(-0.01053049862020f), Qfmt15(-0.91266367957293f),
    Qfmt15(0.54840422910309f), Qfmt15(0.40009252867955f), Qfmt15(-0.99867974711855f), Qfmt15(-0.95531076805040f),
    Qfmt15(-0.45725933317144f), Qfmt15(-0.72929675029275f), Qfmt15(0.75622801399036f), Qfmt15(0.07069442601050f),
    Qfmt15(0.74496252926055f), Qfmt15(-0.96440182703856f), Qfmt15(0.30424629369539f), Qfmt15(0.66565033746925f),
    Qfmt15(0.91697008020594f), Qfmt15(-0.70774918760427f), Qfmt15(-0.70051415345560f), Qfmt15(-0.99496513054797f),
    Qfmt15(0.98164490790123f), Qfmt15(-0.54671580548181f), Qfmt15(-0.01689629065389f), Qfmt15(-0.86110349531986f),
    Qfmt15(-0.98892980586032f), Qfmt15(0.51756627678691f), Qfmt15(-0.99635026409640f), Qfmt15(-0.99969370862163f),
    Qfmt15(0.55266258627194f), Qfmt15(0.34581177741673f), Qfmt15(0.62664209577999f), Qfmt15(-0.77149701404973f),
    Qfmt15(-0.91592244254432f), Qfmt15(-0.76285492357887f), Qfmt15(0.79788337195331f), Qfmt15(0.54473080610200f),
    Qfmt15(-0.85639281671058f), Qfmt15(-0.92882402971423f), Qfmt15(-0.11708371046774f), Qfmt15(0.21356749817493f),
    Qfmt15(-0.76191692573909f), Qfmt15(0.98111043100884f), Qfmt15(-0.85913269895572f), Qfmt15(-0.93307242253692f),
    Qfmt15(0.30485754879632f), Qfmt15(0.85289650925190f), Qfmt15(0.91328082618125f), Qfmt15(-0.05890199924154f),
    Qfmt15(0.28398686150148f), Qfmt15(0.95258164539612f), Qfmt15(-0.78566324168507f), Qfmt15(-0.95789495447877f),
    Qfmt15(0.82411158711197f), Qfmt15(-0.65185446735885f), Qfmt15(-0.93643603134666f), Qfmt15(0.91427159529618f),
    Qfmt15(-0.70395684036886f), Qfmt15(0.00563771969365f), Qfmt15(0.89065051931895f), Qfmt15(-0.68683707712762f),
    Qfmt15(0.72165342518718f), Qfmt15(-0.62928247730667f), Qfmt15(0.29938434065514f), Qfmt15(-0.91781958879280f),
    Qfmt15(0.99298717043688f), Qfmt15(0.82368298622748f), Qfmt15(-0.98512833386833f), Qfmt15(-0.95915368242257f),
    Qfmt15(-0.21411126572790f), Qfmt15(-0.68821476106884f), Qfmt15(0.91851997982317f), Qfmt15(-0.96062769559127f),
    Qfmt15(0.51646184922287f), Qfmt15(0.61130721139669f), Qfmt15(0.47336129371299f), Qfmt15(0.90998308703519f),
    Qfmt15(0.44844799194357f), Qfmt15(0.66614891079092f), Qfmt15(0.74922239129237f), Qfmt15(-0.99571588506485f),
    Qfmt15(0.97401082477563f), Qfmt15(0.72683747733879f), Qfmt15(0.95432193457128f), Qfmt15(-0.72962208425191f),
    Qfmt15(-0.85359479233537f), Qfmt15(-0.81412430338535f), Qfmt15(-0.87930772356786f), Qfmt15(-0.71573331064977f),
    Qfmt15(0.83524300028228f), Qfmt15(-0.48086065601423f), Qfmt15(0.97139128574778f), Qfmt15(0.51992825347895f),
    Qfmt15(-0.00848591195325f), Qfmt15(-0.70294374303036f), Qfmt15(-0.95894428168140f), Qfmt15(0.97079252950321f),
    Qfmt15(-0.92404293670797f), Qfmt15(-0.69506469500450f), Qfmt15(0.26559203620024f), Qfmt15(0.28038443336943f),
    Qfmt15(-0.74138124825523f), Qfmt15(-0.01752795995444f), Qfmt15(-0.55126773094930f), Qfmt15(0.97960898850996f),
    Qfmt15(-0.99196309146936f), Qfmt15(-0.67684928085260f), Qfmt15(0.09140039465500f), Qfmt15(-0.71658965751996f),
    Qfmt15(0.81014640078925f), Qfmt15(0.40616991671205f), Qfmt15(-0.67680188682972f), Qfmt15(0.86849774348749f),
    Qfmt15(-0.99500381284851f), Qfmt15(0.84329189340667f), Qfmt15(-0.09215968531446f), Qfmt15(0.99956173327206f),
    Qfmt15(-0.79732779473535f), Qfmt15(0.96349973642406f), Qfmt15(-0.79942778496547f), Qfmt15(-0.11566039853896f),
    Qfmt15(-0.39922954514662f), Qfmt15(0.99089197565987f), Qfmt15(0.28631285179909f), Qfmt15(-0.83302725605608f),
    Qfmt15(0.95404443402072f), Qfmt15(-0.06449863579434f), Qfmt15(-0.99575054486311f), Qfmt15(-0.65501142790847f),
    Qfmt15(-0.81254441908887f), Qfmt15(-0.99646369485481f), Qfmt15(0.00287840603348f), Qfmt15(0.70176989408455f),
    Qfmt15(0.96361882270190f), Qfmt15(-0.68883758192426f), Qfmt15(-0.34875585502238f), Qfmt15(0.91980081243087f),
    Qfmt15(-0.99009048343881f), Qfmt15(0.68865791458395f), Qfmt15(-0.99484402129368f), Qfmt15(0.94214511408023f),
    Qfmt15(-0.67414626793544f), Qfmt15(-0.47339353684664f), Qfmt15(0.14323651387360f), Qfmt15(-0.29268293575672f),
    Qfmt15(0.43793861458754f), Qfmt15(-0.36345126374441f), Qfmt15(-0.08750604656825f), Qfmt15(-0.96495267812511f),
    Qfmt15(0.55526940659947f), Qfmt15(0.73538215752630f), Qfmt15(-0.30889773919437f), Qfmt15(0.03574995626194f),
    Qfmt15(0.98720684660488f), Qfmt15(-0.81689296271203f), Qfmt15(0.67866860118215f), Qfmt15(-0.15808569732583f),
    Qfmt15(0.80723395114371f), Qfmt15(0.47788757329038f), Qfmt15(0.96367554763201f), Qfmt15(-0.99143875716818f),
    Qfmt15(0.83081876925833f), Qfmt15(-0.58753191905341f), Qfmt15(0.95538108220960f), Qfmt15(-0.96490920476211f),
    Qfmt15(-0.97327101028521f), Qfmt15(0.91400366022124f), Qfmt15(-0.99925837363824f), Qfmt15(-0.86875903507313f),
    Qfmt15(-0.26240034795124f), Qfmt15(-0.24664412953388f), Qfmt15(0.02416275806869f), Qfmt15(0.82068619590515f),
    Qfmt15(0.88547373760759f), Qfmt15(-0.18173078152226f), Qfmt15(0.09355476558534f), Qfmt15(-0.54668414224090f),
    Qfmt15(0.37050990604091f), Qfmt15(-0.70373594262891f), Qfmt15(-0.34600785879594f), Qfmt15(-0.68774481731008f),
    Qfmt15(-0.26843291251234f), Qfmt15(0.49072334613242f), Qfmt15(0.38975993093975f), Qfmt15(-0.97757125224150f),
    Qfmt15(-0.17325552859616f), Qfmt15(0.99948035025744f), Qfmt15(-0.64946246527458f), Qfmt15(-0.12016920576437f),
    Qfmt15(-0.58947456517751f), Qfmt15(-0.41815140454465f), Qfmt15(0.99885650204884f), Qfmt15(-0.56649614128386f),
    Qfmt15(0.94138021032330f), Qfmt15(-0.75725076534641f), Qfmt15(0.20541973692630f), Qfmt15(0.99980371023351f),
    Qfmt15(0.29078277605775f), Qfmt15(-0.62858772103030f), Qfmt15(0.43440904467688f), Qfmt15(-0.98298583762390f),
    Qfmt15(0.19513029146934f), Qfmt15(-0.95476662400101f), Qfmt15(0.93379635304810f), Qfmt15(-0.85235410573336f),
    Qfmt15(-0.86425093011245f), Qfmt15(0.38879779059045f), Qfmt15(0.92045124735495f), Qfmt15(0.89162532251878f),
    Qfmt15(-0.36834336949252f), Qfmt15(0.93891760988045f), Qfmt15(0.99267657565094f), Qfmt15(-0.94063471614176f),
    Qfmt15(0.99740224117019f), Qfmt15(-0.35899413170555f), Qfmt15(0.05237237274947f), Qfmt15(0.36703583957424f),
    Qfmt15(0.91653180367913f), Qfmt15(0.69000803499316f), Qfmt15(-0.38658751133527f), Qfmt15(-0.29250814029851f),
    Qfmt15(-0.60182204677608f), Qfmt15(-0.97418588163217f), Qfmt15(0.88461574003963f), Qfmt15(0.05198933055162f),
    Qfmt15(-0.53499621979720f), Qfmt15(-0.49429560226497f), Qfmt15(-0.98935142339139f), Qfmt15(-0.98081380091130f),
    Qfmt15(-0.27338148835532f), Qfmt15(0.06310802338302f), Qfmt15(-0.20461677199539f), Qfmt15(0.66223843141647f),
    Qfmt15(-0.84764345483665f), Qfmt15(-0.89039863483811f), Qfmt15(0.95903308477986f), Qfmt15(0.73504123909879f),
    Qfmt15(-0.31744434966056f), Qfmt15(-0.34110827591623f), Qfmt15(0.47803883714199f), Qfmt15(0.98299195879514f),
    Qfmt15(-0.30963073129751f), Qfmt15(0.99992588229018f), Qfmt15(-0.93149731080767f), Qfmt15(0.99923472302773f),
    Qfmt15(-0.26024169633417f), Qfmt15(-0.35712514743563f), Qfmt15(-0.99899084509530f), Qfmt15(0.86557171579452f),
    Qfmt15(0.33408042438752f), Qfmt15(0.99010736374716f), Qfmt15(-0.66694269691195f), Qfmt15(0.64016792079480f),
    Qfmt15(0.99570534804836f), Qfmt15(-0.63431466947340f), Qfmt15(-0.07706847005931f), Qfmt15(0.98590090577724f),
    Qfmt15(0.80099335254678f), Qfmt15(0.78368131392666f), Qfmt15(0.08707806671691f), Qfmt15(-0.86811883080712f),
    Qfmt15(-0.39466529740375f), Qfmt15(0.97875325649683f), Qfmt15(-0.95038560288864f), Qfmt15(0.17005239424212f),
    Qfmt15(-0.76910792026848f), Qfmt15(0.99743281016846f), Qfmt15(0.95437383549973f), Qfmt15(0.99578905365569f),
    Qfmt15(0.28058259829990f), Qfmt15(0.85256524470573f), Qfmt15(-0.50608540105128f), Qfmt15(-0.97210735183243f),
    Qfmt15(0.95424048234441f), Qfmt15(-0.96926570524023f), Qfmt15(0.30872163214726f), Qfmt15(-0.24523839572639f),
    Qfmt15(-0.33813265086024f), Qfmt15(-0.05826828420146f), Qfmt15(-0.22898461455054f), Qfmt15(-0.18509915019881f),
    Qfmt15(-0.10488238045009f), Qfmt15(-0.71886586182037f), Qfmt15(0.99793873738654f), Qfmt15(0.57563307626120f),
    Qfmt15(0.28909646383717f), Qfmt15(0.42188998312520f), Qfmt15(0.93335049681047f), Qfmt15(-0.97087374418267f),
    Qfmt15(0.36722871286923f), Qfmt15(-0.81093025665696f), Qfmt15(-0.26240603062237f), Qfmt15(0.83996497984604f),
    Qfmt15(-0.99909615720225f), Qfmt15(0.74649464155061f), Qfmt15(-0.74774595569805f), Qfmt15(0.95781667469567f),
    Qfmt15(0.95472308713099f), Qfmt15(0.48708332746299f), Qfmt15(0.46332038247497f), Qfmt15(-0.76497004940162f),
    Qfmt15(0.57397389364339f), Qfmt15(0.75374316974495f), Qfmt15(-0.59174397685714f), Qfmt15(0.75087906691890f),
    Qfmt15(-0.98607857336230f), Qfmt15(-0.40761056640505f), Qfmt15(0.66929266740477f), Qfmt15(-0.97463695257310f),
    Qfmt15(0.90145509409859f), Qfmt15(-0.87259289048043f), Qfmt15(-0.91529461447692f), Qfmt15(-0.03305738840705f),
    Qfmt15(0.07223051368337f), Qfmt15(0.99498012188353f), Qfmt15(-0.74904939500519f), Qfmt15(0.04585228574211f),
    Qfmt15(-0.89054954257993f), Qfmt15(-0.83782144651251f), Qfmt15(0.33454804933804f), Qfmt15(-0.99707579362824f),
    Qfmt15(-0.22827527843994f), Qfmt15(0.67248046289143f), Qfmt15(-0.05146538187944f), Qfmt15(0.99947295749905f),
    Qfmt15(0.66951124390363f), Qfmt15(-0.99602956559179f), Qfmt15(0.82104905483590f), Qfmt15(0.99186510988782f),
    Qfmt15(-0.65284592392918f), Qfmt15(0.93885443798188f), Qfmt15(0.96735248738388f), Qfmt15(-0.22225968841114f),
    Qfmt15(-0.44132783753414f), Qfmt15(-0.85694974219574f), Qfmt15(0.91783042091762f), Qfmt15(0.72556974415690f),
    Qfmt15(-0.99711581834508f), Qfmt15(0.77638976371966f), Qfmt15(0.07717324253925f), Qfmt15(-0.56049829194163f),
    Qfmt15(0.98398893639988f), Qfmt15(0.47546946844938f), Qfmt15(0.65675089314631f), Qfmt15(0.03273375457980f),
    Qfmt15(-0.38684144784738f), Qfmt15(-0.97346267944545f), Qfmt15(-0.53282156061942f), Qfmt15(0.99817310731176f),
    Qfmt15(-0.50254500772635f), Qfmt15(0.01995873238855f), Qfmt15(0.99930381973804f), Qfmt15(0.82907767600783f),
    Qfmt15(-0.58660709669728f), Qfmt15(-0.17573736667267f), Qfmt15(0.83434292401346f), Qfmt15(0.05946491307025f),
    Qfmt15(0.81505484574602f), Qfmt15(-0.44976380954860f), Qfmt15(-0.89746474625671f), Qfmt15(0.39677256130792f),
    Qfmt15(-0.07588948563079f), Qfmt15(0.76343198951445f), Qfmt15(-0.74490104699626f), Qfmt15(0.64880119792759f),
    Qfmt15(0.62319537462542f), Qfmt15(0.42215817594807f), Qfmt15(0.02704554141885f), Qfmt15(0.80001773566818f),
    Qfmt15(-0.79351832348816f), Qfmt15(0.63872359151636f), Qfmt15(0.52890520960295f), Qfmt15(0.74238552914587f),
    Qfmt15(0.99096131449250f), Qfmt15(-0.80412329643109f), Qfmt15(-0.64612616129736f), Qfmt15(0.11657770663191f),
    Qfmt15(-0.95053182488101f), Qfmt15(-0.62228872928622f), Qfmt15(0.03004475787316f), Qfmt15(-0.97987214341034f),
    Qfmt15(-0.99986980746200f), Qfmt15(0.89110648599879f), Qfmt15(0.10407960510582f), Qfmt15(0.95964737821728f),
    Qfmt15(0.50843233159162f), Qfmt15(0.17006334670615f), Qfmt15(0.25872675063360f), Qfmt15(-0.01115998681937f),
    Qfmt15(-0.79598702973261f), Qfmt15(-0.99264708948101f), Qfmt15(-0.99829663752818f), Qfmt15(-0.70801016548184f),
    Qfmt15(-0.70467057786826f), Qfmt15(0.99846021905254f), Qfmt15(-0.63364968534650f), Qfmt15(-0.16258217500792f),
    Qfmt15(-0.43645594360633f), Qfmt15(-0.99848471702976f), Qfmt15(-0.16796458968998f), Qfmt15(-0.87979225745213f),
    Qfmt15(0.44183099021786f), Qfmt15(0.93310180125532f), Qfmt15(-0.93941931782002f), Qfmt15(-0.88590003188677f),
    Qfmt15(0.99971463703691f), Qfmt15(-0.75376385639978f), Qfmt15(0.93887685615875f), Qfmt15(0.85126435782309f),
    Qfmt15(0.39701421446381f), Qfmt15(-0.37024464187437f), Qfmt15(-0.36024828242896f), Qfmt15(-0.93388812549209f),
    Qfmt15(-0.65298804552119f), Qfmt15(0.11960319006843f), Qfmt15(0.94292565553160f), Qfmt15(0.75081145286948f),
    Qfmt15(0.56721979748394f), Qfmt15(0.46857766746029f), Qfmt15(0.97312313923635f), Qfmt15(-0.38299976567017f),
    Qfmt15(0.41025800019463f), Qfmt15(0.09638062008048f), Qfmt15(-0.85283249275397f), Qfmt15(0.88866808958124f),
    Qfmt15(-0.48202429536989f), Qfmt15(0.27572582416567f), Qfmt15(-0.65889129659168f), Qfmt15(0.98838086953732f),
    Qfmt15(-0.20651349620689f), Qfmt15(-0.62126416356920f), Qfmt15(0.20320105410437f), Qfmt15(-0.97790548600584f),
    Qfmt15(0.11112534735126f), Qfmt15(-0.41368337314182f), Qfmt15(0.24133038992960f), Qfmt15(-0.66393410674885f),
    Qfmt15(-0.53697829178752f), Qfmt15(-0.97224737889348f), Qfmt15(0.87392477144549f), Qfmt15(0.19050361015753f),
    Qfmt15(-0.46353441212724f), Qfmt15(-0.07064096339021f), Qfmt15(-0.92444085484466f), Qfmt15(-0.83822593578728f),
    Qfmt15(0.75214681811150f), Qfmt15(-0.42102998829339f), Qfmt15(-0.72094786237696f), Qfmt15(0.78843311019251f),
    Qfmt15(0.97394027897442f), Qfmt15(0.99206463477946f), Qfmt15(0.76789609461795f), Qfmt15(-0.82002421836409f),
    Qfmt15(0.81924990025724f), Qfmt15(-0.26719850873357f), Qfmt15(-0.43311260380975f), Qfmt15(0.99194979673836f),
    Qfmt15(-0.80692001248487f), Qfmt15(0.43080003649976f), Qfmt15(0.67709491937357f), Qfmt15(0.56151770568316f),
    Qfmt15(0.10831862810749f), Qfmt15(0.91229417540436f), Qfmt15(-0.48972893932274f), Qfmt15(-0.89033658689697f),
    Qfmt15(0.65269447475094f), Qfmt15(0.67439478141121f), Qfmt15(-0.47770832416973f), Qfmt15(-0.99715979260878f),
    Qfmt15(-0.90889593602546f), Qfmt15(-0.06618622548177f), Qfmt15(0.99430266919728f), Qfmt15(0.97686402381843f),
    Qfmt15(0.94813650221268f), Qfmt15(-0.95434497492853f), Qfmt15(-0.49104783137150f), Qfmt15(0.99881175120751f),
    Qfmt15(0.50449166760303f), Qfmt15(0.47162891065108f), Qfmt15(-0.62081581361840f), Qfmt15(-0.43867015250812f),
    Qfmt15(0.98630563232075f), Qfmt15(-0.61510362277374f), Qfmt15(-0.03841517601843f), Qfmt15(-0.30102157304644f),
    Qfmt15(0.41881284182683f), Qfmt15(-0.86135454941237f), Qfmt15(0.67226861393788f), Qfmt15(-0.70737398842068f),
    Qfmt15(0.94044946687963f), Qfmt15(-0.82386352534327f), Qfmt15(-0.32070666698656f), Qfmt15(0.57593163224487f),
    Qfmt15(-0.36326018419965f), Qfmt15(0.99979044674350f), Qfmt15(-0.92366023326932f), Qfmt15(-0.44607178518598f),
    Qfmt15(0.44226800932956f), Qfmt15(0.03671907158312f), Qfmt15(0.52175424682195f), Qfmt15(-0.94701139690956f),
    Qfmt15(-0.98759606946049f), Qfmt15(0.87434794743625f), Qfmt15(-0.93412041758744f), Qfmt15(0.96063943315511f),
    Qfmt15(0.97534253457837f), Qfmt15(0.99642466504163f), Qfmt15(-0.94705089665984f), Qfmt15(0.91599807087376f)
};


#ifdef HQ_SBR


const Int32 fir_table[5][5] =
{
    { Q30_fmt(1.0f)},
    { Q30_fmt(0.33333333333333f), Q30_fmt(0.66666666666666f)},
    { Q30_fmt(0.12500000000000f), Q30_fmt(0.37500000000000f),
      Q30_fmt(0.50000000000000f)},
    { Q30_fmt(0.05857864376269f), Q30_fmt(0.20000000000000f),
      Q30_fmt(0.34142135623731f), Q30_fmt(0.40000000000000f)},
    { Q30_fmt(0.03183050093751f), Q30_fmt(0.11516383427084f),
      Q30_fmt(0.21816949906249f), Q30_fmt(0.30150283239582f),
      Q30_fmt(0.33333333333333f)}
};



const Int32 rPxx[512] =
{

    0x8010B3DB,  0x7C4DA98F, 0x12168648, 0xC3D4D033,
    0x674D25F5,  0xCE1972A6, 0xFEA5AA4A, 0x8B2DF13E,
    0x46326048,  0x3336815E, 0x802A8F2B, 0x85B7745C,
    0xC577B766,  0xA2A5828C, 0x60CB1AD1, 0x090C9BD7,
    0x5F5A8B4D,  0x848D86BB, 0x26F1C0B7, 0x553352C1,
    0x755E166B,  0xA5674343, 0xA654C5F5, 0x80A48CB4,
    0x7DA69CD8,  0xBA04FCB4, 0xFDD4005E, 0x91C63676,
    0x816A8F82,  0x423F55AA, 0x8077B59E, 0x80097DE9,
    0x46BD4C18,  0x2C437971, 0x5035A0C2, 0x9D3ED49F,
    0x8AC204B8,  0x9E5A8B0A, 0x662088B9, 0x45B9F0BC,
    0x9261364F,  0x891B23AD, 0xF1028040, 0x1B568BE1,
    0x9E787FB3,  0x7D94854D, 0x92077A94, 0x88903F45,
    0x2705A5B4,  0x6D2B3BDC, 0x74E58034, 0xF8745A8C,
    0x24592C54,  0x79EDB9BB, 0x9B6E9F44, 0x8563E5DA,
    0x697C7BB7,  0xAC8F8E6A, 0x88227FD5, 0x7506822F,
    0xA5E34B42,  0x00B94F10, 0x72004390, 0xA814676E,
    0x5C5EA758,  0xAF721171, 0x2652C50C, 0x8A84A142,
    0x7F19343E,  0x696EA13B, 0x81E68008, 0x853980F9,
    0xE4968869,  0xA7E7DD92, 0x75910BFA, 0x85092E35,
    0x421BA4A3,  0x4E3F3C18, 0x3C97DD02, 0x74797BCB,
    0x39667EFD,  0x55447BA2, 0x5FE68CF3, 0x808B4390,
    0x7CABEA6B,  0x5D08C27A, 0x7A265820, 0xA29A9DF0,
    0x92BC7195,  0x97CA8338, 0x8F725FAD, 0xA46281D3,
    0x6AE86B23,  0xC2728178, 0x7C566684, 0x428C66B7,
    0xFEE89DDB,  0xA60546DC, 0x8540C89D, 0x7C420BF0,
    0x89B86D72,  0xA7077E3F, 0x21FF5DD7, 0x23E3129C,
    0xA1197F1D,  0xFDC0963F, 0xB96F8168, 0x7D6387A6,
    0x810655C8,  0xA95C102B, 0x0BB3E5B4, 0xA44682D4,
    0x67B244C3,  0x33FDDE1D, 0xA95D78F5, 0x6F2AE887,
    0x80A3FC9F,  0x6BF00D52, 0xF4325902, 0x7FF1F02C,
    0x99F08AC5,  0x7B537BB2, 0x99AB5255, 0xF1302497,
    0xCCE4787B,  0x7ED58A28, 0x24A68B79, 0x955EA9D0,
    0x7A1D3EED,  0xF7BD0429, 0x808A3642, 0xAC2769A8,
    0x97FDBDE9,  0x80736C25, 0x005E52E7, 0x59D3E5D0,
    0x7B57341A,  0xA7D374E9, 0xD35A5B7B, 0x75BB5520,
    0x81446DE8,  0x5825473E, 0x80A8E653, 0x78978062,
    0xA9B43F6B,  0xC366920A, 0x1255877D, 0xDA88075F,
    0x380E9AFF,  0xD1795309, 0xF4CB7D09, 0x847BBAED,
    0x471364FA,  0x5E207B74, 0xD87498BF, 0x0493836B,
    0x7E5C3DF6,  0x976F8BBC, 0x56DE680A, 0xEBC26D28,
    0x6753E05B,  0x3D2BC4B0, 0x7B593143, 0x8118E010,
    0x6A5786AD,  0xB4CA01A7, 0x7A49927C, 0x847DAE0C,
    0x836B0FD8,  0x74FD4A34, 0x80175AFC, 0x90CBE605,
    0xDE68A89E,  0xE06C8FD0, 0x031822CE, 0x690B9315,
    0x71568D43,  0xE8BBDE85, 0x0BFA4633, 0xBA057ADA,
    0x2F6CB34F,  0xA5EB74C5, 0xD3B480B6, 0xA7F7D94A,
    0xDDA26A63,  0x3ED0C5EF, 0x31E37A42, 0x82DE06CB,
    0xE9D18940,  0x7FEE4A9A, 0xACDD57DD, 0xF09CB6D9,
    0xB48BD364,  0xCA7814D5, 0x7FDA0E41, 0xB77C8C2A,
    0x787E2D29,  0x9F1144AC, 0x1A4B871E, 0x7FF96630,
    0x25382D4D,  0xAF89319E, 0x379A81DB, 0x822D1AE8,
    0x18FA875E,  0x85C97DE7, 0x7786A544, 0x92E5F550,
    0x915FC560,  0x31C47C82, 0x75D0B014, 0x72204656,
    0xD0D87B76,  0x782E8CD6, 0x7F0FFB2F, 0x879834E7,
    0x7FAAEA73,  0xD20BC44E, 0x06B4DF2C, 0x2EFBCE84,
    0x7550D8D7,  0x5851746A, 0xCE837F5C, 0xDA8D2FEE,
    0xB2F66F13,  0x834D7B7A, 0x713A499C, 0x06A81B39,
    0xBB847C77,  0xC0B97DAC, 0x815CCC7A, 0x8274A2BD,
    0xDD007FEF,  0x0814BA2F, 0xE5CDEDCE, 0x54C45CD5,
    0x937F0309,  0x8E0671BF, 0x7AC1623B, 0x5E15FB32,
    0xD75CD0D9,  0xD4553378, 0x3D30CD88, 0x7DD2028C,
    0xD85CE8DB,  0x7FFDDE5A, 0x88C48228, 0x7FE6996A,
    0xDEAF9EB7,  0xD24818B4, 0x80205F8B, 0x6ECA4728,
    0x2AC36E51,  0x7EBB05E4, 0xAAA08AB1, 0x51F01408,
    0x7F723AAE,  0xAECD1AFB, 0xF6218D55, 0x7E3170F2,
    0x6686D0D3,  0x644F3A3F, 0x0B256799, 0x90E0325D,
    0xCD7AAA7B,  0x7D47A33C, 0x865972A3, 0x15C445FE,
    0x9D8D84D3,  0x7FAB36A7, 0x7A287C29, 0x7F75BABD,
    0x23EA92BC,  0x6D20AD59, 0xBF37ABB6, 0x8391E26E,
    0x7A2480F8,  0x83EE5E6E, 0x27843523, 0xE09A50E7,
    0xD4B6CE82,  0xF889F71C, 0xE2AF7C3A, 0xE84D3CE2,
    0xF2918FA6,  0xA3FB63E0, 0x7FBB7340, 0x49AE8B79,
    0x25017B45,  0x36003DA1, 0x7777C844, 0x83B96EE4,
    0x2F015392,  0x98320B3C, 0xDE68893F, 0x6B834779,
    0x801D8516,  0x5F8C0F8C, 0xA049DD90, 0x7A999AD0,
    0x7A33F500,  0x3E587FFF, 0x3B4E0E09, 0x9E147230,
    0x49772D2B,  0x607A7BC7, 0xB4408D8F, 0x601CDA17,
    0x81C7200B,  0xCBD28CBD, 0x55AB7E3E, 0x833EFFC0,
    0x73627FB7,  0x904E7F04, 0x8AD7EBE6, 0xFBC3D05F,
    0x093F8E53,  0x7F5B7C47, 0xA01E7FFA, 0x05DE7FC2,
    0x8E01D74D,  0x94C17CF9, 0x2AD2919F, 0x805F7757,
    0xE2C61829,  0x5613FB53, 0xF9688978, 0x7FEE77D6,
    0x55B27E98,  0x8081C6D6, 0x69177F69, 0x7EF45C30,
    0xAC6E42CC,  0x782BA021, 0x7BD17457, 0xE38B491E,
    0xC781895B,  0x924E71B8, 0x757BC4A8, 0x5CDF8020,
    0x805E4A82,  0x636078BA, 0x09E14B0E, 0xB84069A0,
    0x7DF23284,  0x3CDC57D2, 0x54101777, 0x0431A015,
    0xCE7A41B6,  0x8365846A, 0xBBCB8AF9, 0x7FC34E40,
    0xBFAB8E4B,  0x028E6D15, 0x7FE8790F, 0x6A1EF7E6,
    0xB4E97BF4,  0xE980C257, 0x6ACBEF53, 0x079C1A41,
    0x685386CC,  0xC66D3458, 0x8D1F7FCD, 0x32C9A02E,
    0xF6475ED7,  0x61B7356F, 0xA0A6793F, 0x530B34E9,
    0x4FC488D4,  0x3609F61F, 0x0376F90F, 0x6666752C,
    0x9A6DD1A5,  0x51C10A67, 0x43B34CDC, 0x5F0605C0,
    0x7ED7E718,  0x99118EB3, 0xAD4A5C69, 0x0EEC94E8,
    0x865483EA,  0xB05769F0, 0x03D88055, 0x82932EC1,
    0x8003D1E3,  0x720F82B1, 0x0D526304, 0x7AD5D2A3,
    0x41147B04,  0x15C49D9F, 0x211E7FDC, 0xFE907E12,
    0x9A1C7C55,  0x80F08095, 0x80370267, 0xA55F2B1C,
    0xA5CC7763,  0x7FCD81A1, 0xAEE3EAE8, 0xEB2F8532,
    0xC82186A5,  0x80317B31, 0xEA7E814B, 0x8F62A430,
    0x388D883A,  0x776F801B, 0x87C0B7CA, 0x8E9A3CF5,
    0x7FF6949E,  0x9F83010B, 0x782CF18C, 0x6CF54301,
    0x32D168AD,  0xD09A908B, 0xD1E22C5C, 0x887593DE,
    0xAC6AE864,  0x0F4F7FDE, 0x78B16A72, 0x601AD283,
    0x489AE12D,  0x3BFAD96A, 0x7C8E8093, 0xCEF87E19,
    0x348302B6,  0x0C5605A6, 0x92D57516, 0x71BF8056,
    0xC24C8416,  0x234B4B0D, 0xABA84B4F, 0x7E827FFD,
    0xE58F45E1,  0xB079B355, 0x1A0290CA, 0x82D37B40,
    0x0E391B80,  0xCB0B241E, 0x1EE441A8, 0xAB03F56F,
    0xBB438301,  0x838C1C43, 0x6FDCEF9D, 0x1862020D,
    0xC4A98614,  0xF6F38710, 0x89ABF29B, 0x94B4FDD3,
    0x6046800E,  0xCA1A7FA4, 0xA3B7D32F, 0x64EB43A6,
    0x7CA9DDD3,  0x7EFBB705, 0x624A9E0D, 0x9708A1E0,
    0x68DC7F9C,  0xDDCB5832, 0xC88E6D35, 0x7EF77599,
    0x98B6D63B,  0x3724E3F0, 0x56AA85C9, 0x47DFA582,
    0x0DDDF4F3,  0x74C5AB88, 0xC14F480C, 0x8E08A446,
    0x538B545F,  0x56529770, 0xC2D9EA81, 0x805C883B,
    0x8BA84F67,  0xF785E183, 0x7F441814, 0x7D09DB4D,
    0x795C8330,  0x85D79A19, 0xC1242A1B, 0x7FD871E9,
    0x409391EC,  0x3C5EE815, 0xB0885FFF, 0xC7D87FFE,
    0x7E3EBB6A,  0xB1438D6B, 0xFB13A68A, 0xD976F62D,
    0x359B02CD,  0x91BE7EA6, 0x560CEEB8, 0xA5739E04,
    0x78600B8E,  0x968A0B6C, 0xD6F1402E, 0x49B88152,
    0xD17F0986,  0x7FF8EDE8, 0x89C48295, 0xC6E6BA93,
    0x389C5B4C,  0x04B3516A, 0x42C892B0, 0x86C7FDA8,
    0x81956954,  0x6FEA726E, 0x886E34F5, 0x7AF57730,
    0x7CD76E45,  0x7F8A59D7, 0x86C6DA22, 0x753F825E
};


#endif


#endif

