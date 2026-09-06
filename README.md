# Mesure de la valeur efficace (RMS) d'un signal sinusoïdal — STM32F407

Chaîne complète de traitement du signal sur **STM32F407VGT6** : génération numérique d'un
sinus par le **DAC**, réinjection du signal analogique vers l'**ADC**, puis calcul de sa
**valeur efficace (RMS)** en temps réel. Amplitude et fréquence sont réglables par
potentiomètres.

> Projet de microprocesseurs — sujet n°4, 2ᵉ année Génie Électrique (GE2),
> École Nationale d'Ingénieurs de Tunis (ENIT), année universitaire 2025–2026.
> Encadrant : M. Khaled Jelassi.

---

## 1. Objectif

La valeur efficace caractérise l'énergie réellement transportée par un signal alternatif ;
c'est la grandeur de référence pour dimensionner charges et convertisseurs. Le projet met
en œuvre sa mesure numérique de bout en bout, sans composant externe de conditionnement :
le microcontrôleur est à la fois **générateur** et **instrument de mesure**.

```
Table sinus ──> DAC 12 bits (PA4) ──┐
                                    │  bouclage matériel
                       ADC 12 bits <┘
                            │
                            v
              suppression de l'offset (V_REF/2)
                            │
                            v
                    calcul RMS ──> visualisation (debug / oscilloscope)
```

---

## 2. Théorie

Pour un signal `v(t)` de période `T` :

$$V_{eff} = \sqrt{\frac{1}{T}\int_0^T v^2(t)\,dt}$$

Sur un signal échantillonné `v[n]`, après suppression de la composante continue
(`v_ac[n] = v[n] − V_REF/2`, soit 1,65 V) :

$$V_{eff} = \sqrt{\frac{1}{N}\sum_{n=0}^{N-1} v_{ac}^2[n]}$$

Pour un sinus pur, on retrouve bien `V_eff ≈ V_max / √2 ≈ 0,707 · V_max`. La méthode
discrète reste valable même si le signal n'est pas parfaitement sinusoïdal.

---

## 3. Matériel et outils

| Élément | Rôle |
|---|---|
| STM32F407VGT6 (ARM Cortex-M4, 168 MHz) | Génération, acquisition et traitement |
| Keil µVision 5 | Édition, compilation, débogage |
| STM32F4xx Standard Peripheral Library | Configuration DAC, ADC, GPIO, SysTick |
| Oscilloscope | Visualisation du sinus généré |
| Logic Analyzer | Vérification des échantillons et du timing |
| 2 potentiomètres | Réglage de l'amplitude et de la fréquence |

### Câblage

| Broche | Fonction |
|---|---|
| `PA4` | Sortie DAC **et** entrée ADC (bouclage de mesure) |
| `PC1` | Potentiomètre — amplitude du signal |
| `PC2` | Potentiomètre — fréquence du signal |

---

## 4. Fonctionnement logiciel

La cadence est donnée par l'**interruption SysTick**. À chaque interruption :

1. l'échantillon suivant de la table sinus est écrit dans le DAC ;
2. l'ADC convertit la tension présente sur `PA4` ;
3. l'échantillon est accumulé pour le calcul RMS ;
4. les potentiomètres sont lus pour mettre à jour l'amplitude et le **diviseur de
   fréquence** (l'avance dans la table sinus), le tout dans le respect du théorème de
   Shannon–Nyquist.

### Organisation des sources

| Fichier | Rôle |
|---|---|
| `main.c` | Initialisation et boucle principale |
| `config.c` | Configuration des horloges, GPIO et SysTick |
| `dac.c` | Génération du sinus (table de valeurs) |
| `ADC.c` | Acquisition de la tension de retour |
| `conversion_AN.c` | Conversion des codes ADC en tension et calcul de la valeur efficace |
| `startup_stm32f411xe.s` | Code de démarrage |
| `librairie/` | STM32F4xx Standard Peripheral Library |

---

## 5. Résultats expérimentaux

Le signal généré a été validé à l'oscilloscope et au Logic Analyzer. Le réglage par
potentiomètre permet de balayer la fréquence — mesures relevées à **39 Hz** et **78 Hz** —
et la valeur efficace calculée est cohérente avec la relation théorique `V_max / √2`.

Le rapport complet (`docs/`) détaille l'étude théorique, les schémas blocs, le montage et
les relevés.

---

## 6. Compilation

**Prérequis :** Keil µVision 5 + pack de périphériques STM32F4.

```bash
git clone https://github.com/<ton-compte>/stm32f407-rms-voltmeter.git
```

1. Ouvrir `Projet_micro_sujet4_hamza_maram_2AGE2.uvprojx` dans Keil µVision.
2. `Project > Build Target` (F7).
3. `Debug > Start/Stop Debug Session` (Ctrl+F5) puis `Flash > Download`.

---

## 7. Documentation

- `docs/Rapport.pdf` — rapport final (24 pages)
- `docs/Presentation.pdf` — support de soutenance
- Vidéo de démonstration du montage en fonctionnement

---

## 8. Auteurs

**Maram TURKI** et **Hamza MAMI** — 2ᵉ année Génie Électrique, ENIT
