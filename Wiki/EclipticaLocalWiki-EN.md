# Ecliptica Local Wiki
**Content is for reference only, sourced from[Ecliptica official wiki](https://ecliptica.miraheze.org/wiki/Main_Page)**

## Contents
1. [The flow of a round](#the-flow-of-a-round)
2. [Phase](#phase)
3. [General](#general)
4. [Classes](#classes)
5. [Upgrades](#upgrades)
6. [Status effect](#status-effect)
7. [Runes + Curses](#runes--curses)
8. [Artifacts](#artifacts)
9. [Maps](#maps)


## The flow of a round
1. Choose your class in the Beginning Lobby and equip runes at the Workshop Anvil. 
2. Enter the map (determined by the artifact you brought this stage) and clear enemies wave by wave. 
3. Between stages, go into The In-Between and use tokens to buy upgrades from three Vendors. 
4. Phase progression: each time you hit a shop, the Phase wheel advances, changing the difficulty and enemy composition. 
5. At the end of this stage, challenge the Boss; defeat it to move on to the next stage. 
6. Take your artifact to the Dimensional Portal for sacrifice, and finally face the final Boss in the Eye of the Eclipse.

## Phase
| Phase value range | Stage |
| :---: | :---: |
| 0 < x < 0.2 | Primal |
| 0.2 < x < 0.4 | Penumbral |
| 0.4 < x <0.6 | Antumbral |
| 0.6 < x < 0.8 | Umbral |
| 0.8 < x < 1 | Eclipse |
| 1 | Eye of the Eclipse |

## General
1. Some bosses only appear after their Phase value reaches a certain threshold. 
2. PURPLE attacks ignore your defense, so keep your distance as soon as you see them charging. 
3. Status effects applied to bosses are weakened but still work. 
4. In instances with over 5 players, being the last one alive gives you the ADRENALINE status effect. 
5. Boundary penalties
   >During boss fights, if you stay too close to the map boundary for too long, you’ll start taking two negative effects:
   ><br>“Poisoned” — about 10 damage/sec (based on 100 HP);</br>
   >“Decay” — prevents healing, all recovery methods stop working.
   ><br>Leaving the boundary area stops these effects from applying further, but any debuffs already received won’t disappear.</br>
6. Token/Currency
   >Tokens are the main currency used for upgrades in Ecliptica.
   ><br>Each level randomly spawns 3 Tokens around the map.</br>
   >Tokens look like hexagonal bipyramids.
   ><br>You can spend Tokens on three different Vendors in the shop.</br>
7. Player damage starts to scale down after 6000.
8. The damage that players and enemies can deal is divided into PHYSICAL and ELEMENTAL types. ELEMENTAL damage includes FIRE, FROST, ELECTRIC, LUMINOUS, SHADOW, and POISON. Players can only deal normal damage, while enemies can deal both normal damage and PURPLE damage.

# classes
### Subdirectory
- [Spellsword](#spellsword)
- [Twinmage](#twinmage)
- [Gunmancer](#gunmancer)
- [Fistmage](#fistmage)
- [Spellhammer](#spellhammer)
- [Shield Mage](#shield-mage)
- [Thaumaturge](#thaumaturge)
- [Nekomancer](#nekomancer)

### Spellsword
#### Introduction
You may call yourself a Spellsword, but you were ever really strong enough to wield a sword skillfully. However, who said your magical abilities can't make up for that?
#### Skills
##### Primarily skill: Telekinetic Strike
Swing your sword, dealing 55 PHYSICAL damage.
10% chance to inflict BLEEDING status effect.
##### Secondary skill: Piercing Strike/
Charge for up to X seconds and then release a mid-range piercing attack, dealing 85-170 PHYSICAL damage.
Up to 50% chance to inflict BLEEDING status effect.
>Range, Damage, and Bleed chance increases with charge time.
>Charge time is reduced by Attack Speed.
##### Utility skill: Quick Dash/
Perform a dash in your current movement direction.
3 second cooldown.
>Has a very short period of I-frames at the beginning of the dash.
>Can dash through purple attacks.
#### Class Upgrades
- Spellsword: Proficiency
>Piercing Strike range: +4 (+4 per stack) meters. Hitting an enemy with Telekinetic Strike has a 2.5% (+2.5% per stack) chance to give you X stacks of the FRENZIED status effect.
- Spellsword: Specialization
>PHYSICAL Damage +4% (+4% per stack), Utility Cooldown -6% (-6% per stack)
- Spellsword: Mastery
>Restore 2 (+2 per stack) HP upon dealing damage with the BLEEDING status effect. Health Regeneration -100% (-100% per stack)
- Spellsword: Burst
>Using your Utility skill increases your Attack Speed by 25% (+25% per stack) for 3 seconds. Utility Cooldown Rate -20% (-20% per stack)
- Spellsword: Engagement
>Using Quick Dash will grant you a brief ENFORCED Status Effect. Utility Cooldown +15% (+15% per stack)
- Spellsword: Hemorrhage
>When applying the BLEEDING Status Effect to an enemy with the effect already applied, convert all cumulative stacks into the HEMORRHAGE Status Effect.
- Spellsword: Swift Stab
>Your Piercing Strike damage will be increased by 35% (+35% per stack) of your Movement Speed above 100%.
- Spellsword: Shieldbreaker/
>Your Piercing Strike will penetrate armor, dealing 25% (+25% per stack) of it's base damage. Your base attack will deal an additional 25% (+25% per stack) Damage. Attack Speed -30%
- Spellsword: Whirlwind
>Releasing a fully charged piercing strike will cast a large whirlwind, continuously dealing 11 (+6 per stack) PHYSICAL Damage every 0.2 seconds. Piercing Strike Charge Time +30% (+30% per stack)
#### Editor's Note
To be honest, I haven't played Spellsword, so I'm not really sure how strong it is, but from the skill description, its skill mechanics seem pretty interesting. Also, it feels like Spellsword's damage output is decent, but its survivability is limited, so I wouldn't recommend it for new players.

### Twinmage
#### Introduction
As much as you've always wanted to become a powerful sorcerer, some people just do not have the necessary talent and innate ability. But, you could always just rely on a pair of Elemental Hands to make up for that.
#### Skills
>Twinmage's skills change based on the Hand skills you choose, and you can pick up to two Hand skills. One is your Primary skill, and the other is your Secondary skill.
##### Hand: Flaming Hand
Launch a fireball, dealing 27 FIRE damage.
10% chance to inflict BURNING status effect.
Has a projectile speed of 16m/s and a max distance of 50m.
##### Hand: Ice Hand
Launch a frost missile, dealing 27 FROST damage.
10% chance to inflict FREEZING status effect.
Has a projectile speed of 20m/s and a max distance of 50m.
##### Hand: Electric Hand
Cast a bolt of lightning, dealing 27 ELECTRIC damage.
10% chance to inflict PARALYZED status effect.
Hit scan with a max distance of 50m.
##### Hand: Wind Blade
Launch a whirlwind, dealing 27 PHYSICAL damage.
10% chance to inflict BLEEDING status effect.
Has a projectile speed of 18m/s and a max distance of 50m.
##### Hand: Divine Hand
Launch a ball of light, dealing 35 LUMINOUS damage.
10% chance to apply WEAKENED status effect.
Has a projectile speed of 24m/s and a max distance of 50m.
##### Hand: Profane Hand
Launch a shadow missile, dealing 27 SHADOW damage.
10% chance to apply BREACHED status effect.
Has a projectile speed of 12m/s and a max distance of 50m.
##### Utility skill: Quickwarp
Teleport 15 meters to where you are pointing.
6 second cooldown.
#### Class Upgrades
- Twinmage: Sinistra
>Left Hand Damage +5% (+5% per stack),
>Left Hand Attack Speed +5% (+5% per stack).
>Right Hand Damage -3% (-3% per stack),
>Right Hand Attack Speed -3% (-3% per stack).
>Multiplicative with other Damage and Attack Speeds.
- Twinmage: Dextra
>Right Hand Damage +5% (+5% per stack),
>Right Hand Attack Speed +5% (+5% per stack).
>Left Hand Damage -3% (-3% per stack),
>Left Hand Attack Speed -3% (-3% per stack).
>Multiplicative with other Damage and Attack Speeds.
- Twinmage: Specialization
>Elemental Damage: +7%,
>Projectile Speed: +20%
- Twinmage: Proficiency
>Quickwarp Distance: +5 M (+5 M per stack)
- Twinmage: Rush
>Applying a Status Effect to an enemy will grant you 4 (+2 per stack) stacks of the HASTE status effect.
- Twinmage: Cocktail
>When firing both Elemental Hands at the same time for at least 4 seconds, increase the chance to inflict Status Effects by 10% (+10% per stack)
- Twinmage: Guarded
>Applying a status effect to an enemy will grant you 4 (+2 per stack) stacks of the ENFORCED status effect
- Twinmage: Mastery
>Your Elemental Hand projectiles have a 25% chance to explode in a X (+X per stack) meter radius upon impact, dealing 75% of their damage as splash damage.
- Twinmage: Wicked Sign
>Casting Quickwarp has a 6.7% chance to grant you 8 (+2 per stack) stacks of the EMPOWERED, ENFORCED, HASTE and FRENZIED status effects.
>This will be guaranteed to happen if you are at 67 HP.
- Twinmage: Inflation
>Elemental Hand Projectile Size +150%
- Twinmage: Retaliation
>Taking Damage will grant you 6 (+1 per stack) stacks of the EMPOWERED status effect. 6 second cooldown.
#### Editor's Note
Twinmage is a really interesting class, with unique skill mechanics and gameplay. By choosing different elemental hand skills, players can adjust their damage output according to personal preference and tactical needs. Personally, I recommend a combination of the Electric Hand and any other elemental hand, then choose either the left or right path upgrade based on the Electric Hand's left and right hand bonuses. Almost all upgrades are core upgrades, and there are also some general upgrades you need to pick. From my own experience, Twinmage has the highest DPS (1500, note: this DPS value is under extreme conditions, normally it’s 300-500), so I recommend it for new players.
#### Recommended Upgrades
See [Twinmage.png](./Twinmage.png)

### Gunmancer
#### Introduction
With enough cybernetic enhancements and a brain-interfaced Blast Cannon, anyone can become a Sorcerer these days.
#### Skills
>Gunmancer's Primary and Secondary skills both have options, and you can choose different skills to change the effects, but each skill can only be chosen once.
###### primary skill: VA-11 Blast Cannon
Fire a long-range hit scan attack every 2 seconds which deals 50 ELECTRIC Damage.
Additionally, apply a small explosion where your attack hits, dealing 50% of the projectile's Damage.
Has an 15% chance to apply the PARALYZED debuff to enemies.
###### Primary skill: Kinetic Flechette
Fire a long-range projectile dealing 50 PHYSICAL Damage. The projectile can pierce an enemy, then redirect towards the nearest enemy.
15% Chance to inflict the BLEEDING status effect.
###### Secondary skill: Firebomb
Launch an explosive projectile with high gravity every X seconds which deals 50 FIRE Damage.
This attack explodes in a wide radius when it hits, dealing 100% of the projectile's Damage.
###### Secondary skill: Photon Condenser
Fire fast bullets every 0.25 seconds which deals 10 LUMINOUS Damage.
5% Chance to inflict the WEAKENED status effect.
###### Secondary skill: Antimatter Accelerator
Fire a scattered blast of five projectiles every X seconds which each deal 8 SHADOW Damage. Hold to narrow the spread.
5% Chance to inflict the BREACHED status effect.
###### Utility skill: Airblast
While standing still, launch yourself upwards then gain greatly decreased gravity for a short time. After a short delay, your next skill fired will become CHARGED and deal 200% damage.
While moving, perform a dash in your current movement direction with 75% reduced cooldown.
Whether you're considered moving or not is based exclusively on key input and not velocity.
10 second cooldown.
#### Class Upgrades
- Gunmancer: Overcharged (VA-11 Blast Cannon)
>VA-11 Blast Cannon beam width: +5% (+5% per stack),
>ELECTRIC Damage: +15% (+15% per stack)
- Gunmancer: Penetrator (Kinetic Flechette)
>Your Kinetic Fletchette can redirect itself 1 more time towards the nearest enemy upon hitting an enemy.
- Gunmancer: Proficiency (Firebomb)
>Firebomb explosion radius: +1 m (+1 m per stack),
>FIRE Damage +7%
- Gunmancer: Proficiency (Photon Condenser)
>Photon Condenser Projectile Count +1 (+1 per stack),
>LUMINOUS Damage +7%
- Gunmancer: Proficiency (Antimatter Accelerator)
>Antimatter Accelerator Projectile Count +1 (+1 per stack)
>SHADOW Damage +5%
- Gunmancer: Specialization
>Attack Speed +7%,
>Utility Cooldown -7%
- Gunmancer: Sidestep
>Using your Airblast Dash will grant you 2 (+1 per stack) stacks of the HASTE status effect
- Gunmancer: Bombing Run
>Using your Airblast Dash launches a bomb dealing FIRE Damage. 4 second cooldown.
- Gunmancer: Mastery
>Charged Shot Damage +25% (+25% per stack)
- Gunmancer: Marksman (VA-11 Blast Cannon)
>Periodically throw a coin. Hitting the coin with your Blast Cannon will direct the blast towards the nearest enemy and increase the Damage by 500% (+24% per stack).
>Coin Size +10% (+10% per stack).
>Actually multiplies specifically the explosion, so the practical damage over a normal shot is only 1.66x
- Gunmancer: Lucky Seven
>Every 7th (Seventh) shot of your Primary Skill will deal 50% more Damage.
>Every 4th (Fourth) show of your Primary Skill will deal 50% less Damage.
#### Editor's Note
After the v0.6 update, Gunmancer got a small buff, especially the Kinetic Flechette, which was significantly improved. A turning mechanism was added, making it perform better in group fights. Also, Gilgamesh’s second-stage hitbox is very small and it’s very... twitchy ~~(god of ADHD)~~, so the Kinetic Flechette’s tracking can handle it pretty well. If you upgrade it right, it can actually deal over a thousand DPS in tests (note: this DPS is in extreme cases; normally it’s around 500-650). Recommended for new players.
#### Recommended upgrades
See [Gunmancer (Kinetic Flechette).png](./Gunmancer%20(Kinetic%20Flechette).png)、[Gunmancer (VA-11 Blast Cannon, outdated).png](./Gunmancer%20(VA-11%20Blast%20Cannon,%20outdated).png)
**<br>The editor hasn't played the new version of VA-11 Blast Cannon; the illustrated upgrades are for version 0.5</br>**

### Fistmage
#### Introduction
Someone as musclebrained as you has no reason to become a sorcerer, but you persevered anyway and made it work somehow.
Powerful hybrid tank/damage class with a strong focus on counterattacks.
#### Skills
##### Primary skill: Aura Fist
Charge for up to 1 second and release to punch, dealing 55-100 PHYSICAL damage based on charge level.
##### Secondary skill: Deflecting Swipe
Swipe, dealing 40 PHYSICAL damage.
After the swipe, gain a short window where the next instance of damage you take will be fully deflected. Successfully deflecting an attack will grant you 12 stacks of EMPOWERED and ENFORCED, HEAL you for 10 Health, and instantly reset the cooldown.
If the Deflecting Swipe is a Perfect Parry, you will heal 30 Health.
5 second cooldown.
##### Utility skill: Super Endurance
For 5 seconds, cleanse all negative status effects and enter an enduring stance. During this time you lose 75% movement speed, reduce damage taken by X%, gain 400% increased knockback resistance, and gain increased Aggro draw.
All above stats are multipliers to your base stats and go above any caps.
12 second cooldown.
#### Class Upgrades
- Fistmage: Proficiency
>On a successful Deflecting Swipe, heal 5 (+5 per stack) HP and summon an aura around yourself, healing nearby allies for half of your personal healing
- Fistmage: Specialization
>PHYSICAL Damage +4% (+4% per stack),
>Knockback Resistance +7% (+7% per stack)
- Fistmage: Mach Punch
>Gain additional PHYSICAL Damage equivalent to 25% (+25% per stack) depending on how fast you are currently moving. 7 second cooldown.
>This does not affect DoTs and can only be proc'd by your Primary Skill.
- Fistmage: Mastery
>On a Successful Deflection, the gained EMPOWERED and ENFORCED status effects are increased by 5 (+5 per stack) stack.
>On a Perfect Parry, gain 7 stacks ADRENALINE Status Effect.
>Deflecting Swipe Cooldown -7% (-7% per stack)
- Fistmage: Blast Radius
>Releasing a fully charged Aura Fist will cause an explosion around you dealing FIRE Damage with a 10% chance to inflict the BURNING Status Effect, which knocks enemies back.
>Attack Speed -30%
- Fistmage: Rage
>On a successful Deflecting Swipe, gain +50% more Attack Speed for 4 seconds and grants you 3 (+1 per stack) stacks of the HASTE status effect.
>This may only grant you a maximum of 15 stacks of HASTE.
>Failing a Deflecting Swipe will inflict you with a the BREACHED Status Effect.
- Fistmage: Runner
>While charging Aura Fist, gradually doubles Movement Speed over 10 (-2 per stack) seconds.
>Goes over the movement speed cap.
- Fistmage: Apply Force
>Upon a successful Deflecting Swipe, gain a stack of the APPLY-FORCE status effect. Upon releasing a fully charged Aura Fist punch with the status effect active, fire a Ranged Projectile dealing 50 PHYSICAL Damage and consume a stack of the status effect.
>Deflecting Swipe Cooldown +30% (+30% per stack)
- Fistmage: Extreme Regimen
>Upon using Super Endurance, gain the GREATER RESILIENCE Status Effect, which lets you block an instance of Normal Damage and reduce an instance of a PURPLE attack's Damage in half.。
#### Editor's Note
I've had the chance to play Fistmage a few times. Honestly, players who don't know how to use the deflection mechanic will find it hard to play this class well, and I found it pretty exhausting. Its skill mechanics are really unique, especially the deflection skills. If you can master them, you can gain a huge advantage in battles. I recommend that players with some gaming experience give it a try.

### Spellhammer
#### Introduction
As someone with a high magic aptitude who decided to become a wild barbarian, conventions and common sense won't be the only things you're smashing into pieces.
#### Skills
>Spellhammer's secondary skill has options—you can pick different skills to change its effects, but you can only choose one.
##### Primary skill: Pummel
Swing your hammer to deal 90 PHYSICAL damage and knock enemies back.
Will increase your movement speed by two times during the swing, and is directly scaled with your Movement Speed.
##### Secondary skill: Jump Smash
Jump upwards, then release to slam back down and deal 130 PHYSICAL damage and knock enemies back. Landing on top of an enemy will deal X extra damage per X based on your initial height and launch you back up.
##### Secondary skill: Chuck
Hold, then release to throw your hammer. Damage scales on how long you have held the throwing charge, deal 65-130 PHYSICAL Damage. Projectile Speed is 40 units.
##### Utility skill: Disperse
Release a wide explosion dealing 130 PHYSICAL damage, and jump backwards.
8 second cooldown. The cooldown applies even while in the air, though is much slower.
#### Class Upgrades
- Spellhammer: Proficiency (Jump Smash)
>Knockback Force: +10% (+10% per stack),
>Jump Smash Strength +5% (+5% per stack)
- Spellhammer: Proficiency (Chuck)
>Knockback Force +10% (+10% per stack),
>Chucked Hammer Gravity Drop -10% (-10% per stack)
- Spellhammer: Specialization
>Movement Speed +7%,
>Jump Height +12%
- Spellhammer: Boosted
>Disperse Blast Strength +10%,
>Disperse Blast Damage +10%
- Spellhammer: Mastery (Jump Smash)
>Performing Jump Smash on top of an enemy will reduce the cooldown by 15% (15% per stack)
- Spellhammer: Mastery (Chuck)
>Upon impact, your Chucked Hammer will bounce towards the nearest enemy 1 time (+1 per stack),
>Chucked Hammer Gravity Drop -5% (-5% per stack)
- Spellhammer: Sus-tain (Jump Smash)
>Performing a Jump Smash on an enemy will grant you 4 stacks (+1 per stack) of the REJUVENATION Status Effect.
>Critical Damage -15%
- Spellhammer: Sus-tain (Chuck)
>Performing a Chucked Hammer throw on an enemy will grant you 4 stacks (+1 per stack) of the REJUVENATION Status Effect.
>Critical Damage -15%
- Spellhammer: Concussion (Jump Smash)
>Performing a high-power Jump Smash will deal additional ELECTRIC Damage with a 50% Chance to inflict the PARALYZED Status Effect
- Spellhammer: Concussion (Chuck)
>On a successful hit, spawn an Area of Effect that will deal ELECTRIC Damage with a 50% Chance to inflict the PARALYZED Status Effect.
- Spellhammer: Helldive (Jump Smash)
>A high-power Jump Smash will deal 20% more Damage.
>Jump Height -35%,
>Critical Chance -5%
- Spellhammer: Helldive (Chuck)
>A fully charged Chuck will deal 15% more Damage.
>Projectile Speed -50%,
>Critical Chance -5%
- Spellhammer: Juggernaut (Jump Smash)
>Performing a high-power Jump Smash will grant you a brief ENFORCED Status Effect
- Spellhammer: Juggernaut (Chuck)
>Performing a full-power throw will grant you a brief EMPOWERED Status Effect.
>You may only have a maximum of 5 stacks of EMPOWERED (each upgrade increases this cap by 2)
#### Editor's Note
The editor has tried both of its modes: Jump Smash is better suited for players with some gaming experience, while Chuck is more for beginners. But what they have in common is that they struggle against moving targets. In the current version, where ADHD-like behavior is pretty common, they're a bit at a disadvantage. Still, Spellhammer's single-hit damage is quite impressive (could be around 1000).
#### Recommended upgrades
See [Spellhammer (Chuck).png](./Spellhammer%20(Chuck).png)
<br>No upgrade recommendations for Jump Smash yet (because the editor don't know how to play it well)</br>

### Shield Mage
#### Introduction
You are a kind of sorcerer who was always too scared to get hurt. You know what they say, sometimes defense is the best offense. Or something like that.
#### Skills
##### Primary skill: Offensive Strike
Throw your shield forward, dealing 75 PHYSICAL damage. While using Defensive Stance, bash your shield forward, dealing 50 PHYSICAL damage and knocking enemies back.
##### Secondary skill: Defensive Stance
Hold to defend with your shield, blocking incoming damage that hits it and reducing your movement speed by X%.
When blocking attacks, charge up ICEBURST. When lowering your shield, Deal up to 300 FROST damage in an X meter radius based on the number of ICEBURST charges, up to 50.
##### Utility skill: Evasive Maneuver
For 5 seconds stop yourself in place, creating an impenetrable shield around you and cleansing negative status effects. The shield will reduce PURPLE attack damage by 50% for yourself and you will gain increased Aggro draw. While using Defensive Stance, perform a short dash in your movement direction with 75% reduced coolown.
16 second cooldown.
#### Class Upgrades
- Shield Mage: Proficiency
>Increase the effect area of your Defensive Stance shield by X% (X% per stack)	
- Shield Mage: Specialization
>Defense +2% (+2% per stack),
>Utility Cooldown -8% (-8% per stack)
- Shieldmage: Unbreakable
>Damage received from PURPLE Attacks -5%,
>Damage received from PURPLE Attacks with an active Evasive Maneuver Shield -10%
- Shieldmage: Bulldozer
>Using your Evasive Maneuver Dash will deal FROST Damage in its direction, and knock enemies back.
- Shieldmage: Ice Burst
>Increases charge-up power of Ice Burst for each blocked Attack
- Shieldmage: Mastery
>Increase the size of your Evasive Maneuver shield by X% (X% per stack)
- Shieldmage: Drainshield
>Blocking Damage in your Defensive Stance Heals 5 HP (+3 HP per stack),
>Health Regeneration -100% (-100% per stack)
- Shieldmage: Rally Up
>Using your Evasive Maneuver Shield gives you and your allies around you a brief EMPOWERED status effect
- Shieldmage: Warden
>Using your Evasive Maneuver Shield gives you and all your allies the RESILIENCE status effect, letting them block an instance of Damage,
>Utility Cooldown +50% (+50% per stack)
#### Editor's Note
The editor hasn't played Shield Mage, so can't give a very fair evaluation, but the importance of a shield to a team is obvious, and it's easy to use. Besides having low damage output, it really has no drawbacks.

### Thaumaturge
#### Introduction
In life, everything that gives us pleasure also gives us pain to measure it by.
Damaging enemies builds up LIFE ENERGY.
#### Skills
##### Passive
Damaging enemies builds up LIFE ENERGY, LIFE ENERGY gain is proportional to the Damage you do.
##### Primary skill: Foul Pustule
Fire a ball of poison, dealing 25 POISON damage.
10% chance to inflict 8 stacks of the POISONED status effect.
Has a projectile speed of Xm/s and a max distance of Xm.
##### Secondary skill: Pain Exchange
Spend 25% LIFE ENERGY to HEAL 60 HP to yourself or an ally and cleansing their negative status effects.
Thaumaturge begins with 50% healing received so the base value is halved for yourself.
3 second cooldown.
The cooldown is increased by 75% if you are healing yourself.
##### Utility skill: Soulborne
For 4 seconds enter an absorption stance, doubling movement speed, reducing damage taken by X%, and converting any damage taken into LIFE ENERGY.
All above stats are multipliers to your base stats and go above any caps.
10 second cooldown.
#### Class Upgrades
- Thaumaturge: Keen Eye/
>Pain Exchange range: +15 (+15 per stack) meters
- Thaumaturge: Proficiency
>Pain Exchange Healing amount +5 (+5 per stack),
>Pain Exchange Cooldown: -10% (-10% per stack)
- Thaumaturge: Specialization
>POISON Damage + 6% (+6% per stack),
>Healing Received +4% (+4% per stack)
- Thaumaturge: Mastery
>LIFE ENERGY required to cast Pain Exchange: -3% (-3% per stack)
>This is additive, not multiplicative, Ex. 25% - 3% = 22% life energy cost.
- Thaumaturge: Moribound
>Upon taking damage from a Status Effect, heal 1 HP (+1 HP per stack),
>Healing Received -10% (-10% per stack)
- Thaumaturge: Schadenfreude
>Applying the POISONED Status Effect will grant you a brief HASTE (+3 per stack, max 6) Status Effect
- Thaumaturge: Splitshot
>When using Foul Pustule, fire an extra projectile.
>Projectile Spread +2.5% (+2.5% per stack),
>Projectile Damage -40% (-40% per stack)
- Thaumaturge: Doping
>The target of Pain Exchange will receive 6 (+3 per stack) stacks of the ENFORCED status effect
>If the target of Pain Exchange is yourself, a maximum of 4 stacks of ENFORCED is applied and cannot be pushed past
>If the target of Pain Exchange is someone else, there is a maximum of X stacks of ENFORCED applied
>Pain Exchange Cooldown +15%
- Thaumaturge: Everlife
>Gain the ability to spend 100% LIFE ENERGY to revive a player with the MORTAL CURSE. Doing so will inflict you with 40 (-20 per stack) stacks of the BREACHED and WEAKENED status effects.
>Upon use, reduces Max Health by 25 until the end of the current round.
>LIFE ENERGY gain -10% (-10% per stack)
- Thaumaturge: Splashback
>When healing yourself or an ally, cast an explosion on the target that deals 75 (+25 per stack) POISON damage in a 3 (+3 per stack) meter radius.
#### Editor's Note
Honestly, Thaumaturge has been pretty weak since the game launched, and it really depends on Upgrades. It's almost a set pattern, and without a good understanding of the game, it's hard to play well. But it's also a crucial class in this game. For a 10-person team, it's recommended to have 2 Thaumaturges and a [Nekomancer](#nekomancer) to effectively deal with one of the final bosses, Gilgamesh. It's not recommended for new players.
#### Recommended Upgrades
See [Thaumaturge.png](./Thaumaturge.png)
<br>Also, Thaumaturge: Everlife is a worthwhile upgrade to pick, but in that game shown, I didn't come across this upgrade.</br>

### Nekomancer
#### Introduction
Just because your skeletal remains have been reborn as a magical Lich Necromancer doesn't mean you can't still have your hobbies and personality.
Collect SOULs which periodically spawn around the stage. Slain enemies have chance to leave a SOUL behind.
#### Skills
##### Passive
Collect SOULs which spawn around the stage every 40 seconds. Slain enemies have a X% chance to leave a SOUL behind.
##### Primary skill: Staff of Feline Mortality
Launch a projectile which deals 20 SHADOW damage. Hit enemies will be marked as a target for Undead Kitties.
10% chance to inflict BREACHED status effect.
##### Secondary skill: Call of the Undead
Spend 1 SOUL to summon one of many Undead Kitties.
Using the skill begins the summoning process. Pressing the skill during the summoning process allows you to select your summon, cycling through them.
Summoned Undead Kitties do not inherit upgrades directly. However, they will gain an identical amount of the listed stats that the player gains from any upgrade; Elemental Damage, Overall Damage, Attack Speed, Projectile Speed, Projectile Distance, Crit Chance, Crit Damage, and Status Effect Chance.
The Maximum amount of souls you can hold is 5, souls uncollected will expire after 30 seconds.
>Undead kitties include: Zombie Kitty, which deals 25 shadow damage per attack; Ballista Kitty, which deals 35 physical damage per attack; Balloon Kitty, which deals 36 fire damage per attack; and Totem Kitty, which heals nearby players.
><br>The damage from undead kitties is higher than that of the Nekomancer itself; Totem Kitty can’t move, while the other kitties can move, but they’re pretty slow.</br>
##### Utility skill: Spirit Drift
For 2 seconds, become invincible(**cannot ignore Purple Attacks**) and drift forward.
10 second cooldown.
#### Class Upgrades
- Nekomancer: Proficiency
>Chance for a slain enemy to leave a Soul: +15% (+15% per stack),
>Random Soul spawn rate: +50% (+50% per stack)
- Nekomancer: Specialization
>ELEMENTAL Damage +7%,
>Utility Cooldown -5%
- Nekomancer: Bloated
>Kitties will inherit 20% of your Overall and ELEMENTAL Defense.
>Overall Defense +3%
- Nekomancer: Death Blossom
>Kitty Totem Healing Speed +10% (+10% per stack),
>Kitty Totem Healing Range +1 M (+ XM per stack).
>Any player in range of the Kitty Totem will receive a brief REJUVENATION Status Effect.
>Overall Damage -3% (-3% per stack)
- Nekomancer: Mastery
>For each soul you are holding:
>- Overall Damage +6% (+6% per stack)
>- Health Regeneration +40% (+40% per stack)
- Nekomancer: Soul Detonation/
>Upon the death of a kitty:
>A large explosion of 2 meters (+1.5 meters per stack) dealing X SHADOW Damage will be released with a 50% Chance to inflict X stacks of the the BREACHED status effect
- Nekomancer: Necropact
>With at least 1 summoned kitty:
>600% (-X% per stack) of any Damage taken at low HP will be redirected towards 1 kitty
- Nekomancer: Soul Vortex
>Souls within 200 Meters and in your line of sight will be pulled towards you.
#### Editor's Note
Nekomancer, the most laid-back (questionable) class. After all, you can leave the dealing damage and healing to the cute kitties. You just need to wander around and collect Souls, though placing the Totem Kitty properly is also a bit of an art.
#### Recommended upgrades
See [Nekomancer (outdated).png](./Nekomancer%20(outdated).png)
**<br>This is the upgrade option for version 0.5; the editor hasn’t played a full game of Nekomancer in version 0.6 yet.</br>**

## Upgrades
### Vendors
- [Crystal of Perseverance](#crystal-of-perseverance)
- [Amaterasu](#amaterasu)
- [Chrono Wizard](#chrono-wizard)

#### Crystal of Perseverance
>The Crystal of Perseverance provides upgrades related to your Max HP, Defense, and everything related to survivability.
- Big Belly
>Knockback Resistance +15% (+15% per stack),
>Max HP +5 (+5 per stack)
- Fluffy
>Max HP: +10 (+10 per stack)
- Gluttonous
>Received Healing +7% (+7% per stack)
- Swarm Enforcer
>Gain +1.5% Defense for each enemy within 32 meters of you. (+1.5% Defense per stack)
- Vitality
>Health Regeneration: +80% (+80% per stack)
- Vital Drain
>Critical strikes recover 2 HP (+2 HP per stack)
- Adrenaline Fiend
>Using your Utility skill recovers 6 (+6 per stack) HP.
>Utility Cooldown Rate +7% (+7% per stack),
>Received Healing -15% (-15% per stack)
- Big and Lazy
>When standing still for at least 1 second, gain 200% (+100% per stack) extra Health Regeneration.
>When moving, set Health Regeneration to 0%.
- Big and Round
>Knockback Resistance: +50% (+50% per stack),
>Max HP: +30 (+30 per stack).
>Jump Height: -10% (-10% per stack),
>Movement Speed: -10% (-10% per stack)
- Cold Blooded
>Reduce number of stacks taken of the FREEZING status effect by X (X per stack).
>FROST Defense: +15% (+15% per stack),
>FIRE Defense: -15% (-15% per stack)
- Conductive Armor
>PHYSICAL Defense +20% (+20% per stack),
>Reduce number of stacks taken of the BLEEDING status effect by X(+X per stack).
>ELEMENTAL Defense -5% (-5% per stack)
- Elemental Armor
>ELEMENTAL Defense +10% (+10% per stack),
>PHYSICAL Defense -7% (-7% per stack)
- Green Thumb
>Received Healing +15%,
>Health Regeneration -80%
- Holy Blessing
>Falling to LOW HP will cause a large explosion dealing 260 (+260 per stack) LUMINOUS damage, with a 100% chance to inflict X stacks of the the WEAKENED status effect.
>LUMINOUS Defense: +15% (+15% per stack),
>SHADOW Defense: +15% (+15% per stack),
>Overall Damage: -5% (-5% per stack)
- Inner Cleanse
>Slightly increases resistance to all negative Status Effects
- Iron Skin
>Defense: +15% (+15% per stack),
>Maximum HP -15 (-15 per stack)
- Last Stand
>Upon taking damage which leaves you at 1-5 HP, receive 3 (+2 per stack) stacks of the INVINCIBLE status effect (each stack of the upgrade increases the HP range by 1).
>Has a 30 second cooldown.
- Life Leech
>Restore 1 (+1 per stack) HP upon dealing damage.
>Overall Damage: -10% (-10% per stack),
>Health Regeneration: -50% (-50% per stack),
>Received Healing -20% (-20% per stack)
- Masochist
>Reduce number of stacks taken of the PARALYZED status effect by X (X per stack).
>ELECTRIC Defense: +15% (+15% per stack),
>PHYSICAL Defense: -10% (-15% per stack)
- Nature's Gift
>Spawn up to 3 (+1 per level) personal Healing Auras at a random location on the stage every 10 seconds which heals you for 20 HP.
- Sacrificial Lamb
>Upon dying, heal every other party member by 25 HP (+25 HP per stack) and X stacks of REJUVENATION (+X per stack).
- Benison of Purification
>Every 4 (-50% per stack) seconds, fire a projectile dealing 25 LUMINOUS damage at the closest enemy within 64 meters.
>SHADOW Defense +10% (+10% per stack),
>Overall Defense -5% (-5% per stack).
>Not influenced by the Attack Speed stat.
>Attack speed caps at 3 stacks.
- Big and Wrathful
>Damage dealt at LOW HP +20%,
>Raise your LOW HP threshold by 20%,
>Defense at LOW HP -25%
- Curse of Wrath
>Every 4 (-50% per stack) seconds, fire a projectile dealing 25 SHADOW damage at the closest enemy within 32 meters.
>LUMINOUS Defense -20% (-20% per stack).
>Not influenced by the Attack Speed stat.
>Attack speed caps at 3 stacks.
- Glass Cannon
>Damage +25% (+25% per stack),
>Health -60 (-60 per stack)
- Healthy Guard
>After being at FULL HP for 15 seconds (-1 second per stack), the next instance of damage you take will be reduced by 50% (+50% per stack)
- Mass Aspect
>Health: +75 (+75 per stack),
>Movement Speed: -30% (-30% per stack)
- Volatile Tenacity
>Upon taking lethal damage when above LOW HP, survive (and take no Damage for 1 second) and be left with 1 HP.
>Cleanses all negative Status Effects upon activation.
>150 second cooldown, increases the cooldown rate by 25% per stack.

#### Amaterasu
>Amaterasu provides upgrades related to Movement Speed, Attack Speed, and Utility Cooldown.
- Athletic
>Movement Speed: +10% (+10% per stack)
- Eagle Eye
>Projectile Speed +35% (+35% per stack)
- Hawkeye
>Projectile Distance +10 M (+10 M per stack),
>Projectile Spread -1% (-1% per stack)
- Panic Sense
>Gain +4% Movement Speed (+4% per stack) for each enemy within 32 Meters of you
- Quick Breath
>Utility Cooldown Rate: +10% (+10% per stack)
- Springfoot
>Jump Height: +20% (+20% per stack)
- Swift Hands
>Attack Speed: +15% (+15% per stack)
- Leg Day
>Reduces number of stacks taken of the HEAVY status effect by X (+X per stack),
>Movement Speed +5% (+5% per stack),
>Jump Height +10% (+10% per stack)
- Reactive Panic
>Taking damage will grant you 5 (+3 per stack) stacks of the FRENZIED status effect
- Smell the Roses
>Falling to low HP will grant you 5 (+2 per stack) stacks of the HASTE status effect with a 30 second Cooldown
- Sniper Vision
>Projectile Distance +25 M (+25 M per stack),
>Projectile Spread -2% (-2% per stack),
>Projectile Speed -45% (-45% per stack)
- Thunder Aura
>Every second inflict 25 (+5 per stack) ELECTRIC Damage in a 4 (+4 per stack) Meter radius around you to enemies.
>Overall Damage: -10% (-10% per stack),
>Movement Speed: -5% (-5% per stack)
- Berserker's Soul (Melee)
>Dealing damage with your main attack grants you a stack of Berserker's Soul, up to 90 stacks.
>Each stack grants you +0.64% (+0.64% per stack) Overall Damage, +1.28% (+1.28% per stack) Attack Speed and -X% Health Regeneration.
>Taking damage sets your stacks to zero.
>Overall Damage: -20% (-20% per stack),
>Attack Speed: -40% (-40% per stack).
>Provides a net total of 45% Overall Damage, 90% Attack Speed and -50% Health Regeneration at max stacks.
- Berserker's Soul (Ranged)
>Dealing damage with your main attack grants you a stack of Berserker's Soul, up to 90 stacks.
>Each stack grants you +0.32% (+0.32% per stack) Overall Damage, +0.64% Attack Speed (+0.64% per stack), and +X% Projectile Spread.
>Taking damage sets your stacks to zero.
>Overall Damage: -10% (-10% per stack),
>Attack Speed: -20% (-20% per stack).
>Provides a net total of 22.5% Overall Damage, 45% Attack Speed and 2% Projectile Spread at max stacks.
- Big and Speedy
>Utility Cooldown Rate: +50% (+50% per stack),
>Overall Defense: -20% (-20% per stack)
- Featherweight
>Movement Speed: +30% (+30% per stack),
>Overall Defense: -10% (-10% per stack)
- Heavy Hand
>Damage +20% (+20% per stack),
>Attack Speed -40% (-40% per stack)
- Partial Flight
>Extra Jump: +1 (+1 per stack)
- Rapid Fire
>Attack Speed: +50% (+50% per stack),
>Overall Damage: -10% (-10% per stack)
- Spray and Pray
>Projectile Speed +125% (+125% per stack),
>Projectile Distance -25 M (-25 M per stack),
>Projectile Spread +2% (+2% per stack)
- Way of the Law
>Periodically switch between the STOP and GO status effects.
>STOP reduces Movement and Attack Speed, but increases Damage.
>GO increases Movement and Attack Speed, but decreases Damage

#### Chrono Wizard
>The Chrono Wizard provides upgrades that tend to be class-specific, or that may not fit into every class. (Ex. Not every class benefits from Projectile Speed by default.)
>SClass Upgrades are included in Chrono Wizard.
- Full Focus
>Critical Strike Chance +5% (+5% per stack)，
>Critical Strike Damage +5% (+5% per stack)
- Potent Strike
>Critical Strikes have a 3% (+3% per stack) higher chance to inflict a Status Effect.
- Sorcerer's Mastery
>ELEMENTAL Damage +7% (+7% per stack)
- Strength
>PHYSICAL Damage +7% (+7% per stack)
- An IQ Too High?
>ELEMENTAL Damage +20% (+20% per stack),
>Projectile Speed -15% (-15% per stack),
>Attack Speed -5% (-5% per stack)
- Clutch or Kick
>Gain +5% (+1% per stack) Overall Damage for every dead player in the party
- Cutting Edge
>Chance to inflict BLEEDING Status Effect +10% (+10% per stack),
>PHYSICAL Defense -5% (-5% per stack)
- Electric Aspect
>ELECTRIC Defense +15% (+15% per stack),
>ELECTRIC Damage +15% (+15% per stack).
>Chance to inflict the PARALYZED Status Effect +5% (+5% per stack),
>PHYSICAL Defense -10% (-10% per stack)
- Fire Aspect
>FIRE Defense +15% (+15% per stack),
>FIRE Damage +15% (+15% per stack).
>Chance to inflict the BURNING Status Effect +5% (+5% per stack),
>FROST Defense -10% (-10% per stack)
- Frost Aspect
>FROST Defense +15% (+15% per stack),
>FROST Damage +15% (+15% per stack).
>Chance to inflict the FROZEN Status Effect +5% (+5% per stack),
>FIRE Defense -10% (-10% per stack)
- Greater Focus
>Critical Strike Chance +10% (+10% per stack),
>Critical Strike Damage +7% (+7% per stack),
>Defense -5% (-5% per stack)
- Luminous Aspect
>LUMINOUS Damage +15% (15% per stack),
>SHADOW Defense +15% (+15% per stack).
>Chance to inflict the WEAKENED Status Effect +5% (+5% per stack),
>ELEMENTAL Defense -5% (-5% per stack)
- Monkey Power
>PHYSICAL Damage +17% (+17% per stack),
>ELEMENTAL Damage -5% (-5% per stack),
>Attack Speed -10% (-10% per stack)
- Poison Aspect
>POISON Damage +15% (+15% per stack),
>POISON Defense +15% (+15% per stack).
>Chance to inflict POISONED Status Effect +10% (+10% per stack),
>Received Healing -8% (-8% per stack)
- Shadow Aspect
>SHADOW Damage +15% (+15% per stack),
>Chance to inflict the BREACHED Status Effect +5% (+5% per stack).
>LUMINOUS Defense -10% (+10% per stack)
- Sticky
>Apply 2 (+2 per stack) additional stacks of Status Effects against enemies.
>Negative Status Effects apply X (+X per stack) additional stacks to you.
- Charged Strike
>Critical Hits will cause an explosion dealing 25 (+10 per stack) PHYSICAL Damage.
>Critical Strike Chance -5% (-5% per stack)
- Flaming Spirit
>When at full HP, performing your primary skill fires a fireball dealing 16 (+8 per stack) FIRE Damage.
>Received Healing -5% (-5% per stack),
>Health Regeneration -20% (-20% per stack)
- Frozen Heart
>When at full HP, performing your primary skill fires an icicle dealing 18 (+9 per stack) FROST damage.
>Received Healing -5% (-5% per stack),
>Health Regeneration -20% (-20% per stack)
- Pocket Abacus
>Every fifth (5th) instance of Damage you deal will become a guaranteed Critical Strike (-1 per stack).
>Critical Strike Damage +10% (+10% per stack),
>Overall Damage -5% (-5% per stack),
>Sets Critical Strike Chance to 0%
- Third Law
>Upon taking Damage, deal 150% (+25% per stack) of it's RAW value to enemies around you as PHYSICAL Damage.
>On Fistmage's Parry, deal 50% of the Damage around you as PHYSICAL Damage
- Warrior's Will
>Using your Utility Skill grants you 5 (+1 per stack) stacks of the EMPOWERED status effect.
>Utility Cooldown Rate -15% (-15% per stack)

## Status effect
- Adrenaline
>Grants +30% to Damage, Movement Speed, Defense etc
- Empowered
>For Players: Increases all sources of damage dealt by 25%,
>For Enemies: Increases all sources of damage dealt by 50%.
>Stacks last for 1.05 seconds.
- Enforced
>Halves damage taken from all sources.
>Stacks last for 1.1 seconds.
>Does not decrease damage of purple attacks
- Frenzied
>Increases attack speed by 50%.
>Stacks last for 1.5 seconds.
- Haste
>Increases movement speed by 50%.
>Stacks last for 1.15 seconds.
- Invincible
>Become invulnerable.
>Stacks last for 1 second.
- Rejuvenation
>Increases the effectiveness of Health Regeneration by 100% and Healing Received by 50%
- Resilience
> Blocks one instance of damage, then removes all stacks.
>Stacks last for 10 seconds.
>Has no effect on purple attacks.
- Greater Resilience
>Universal: Blocks one instance of damage, then removes all stacks.
>Stacks last for 10 seconds.
>Has an effect on purple attacks by reducing the incoming Damage by 50%.
- Breached
>For Players: Increases all damage taken by 75%,
>For Enemies: Increases all damage taken by 25%.
>Stacks last for 0.7 seconds.
- Decayed
>Sets healing received to 0%
>Stacks last for X seconds.
- Frozen
>Each stack deals frost damage when it expires, lasting 0.6 seconds. Each stack has a chance to inflict 'Freeze': movement speed -75%; player's Utility Skill cooldown rate -90%.
- Heavy
>Sets jump height to 0%。
>Stacks last for X seconds
- Paralyzed
>Each stack deals lightning damage when it expires, lasting for 0.3 seconds per stack. Each stack also has a chance to apply 'Rigid': movement speed -99% and unable to attack. It won't interrupt enemies or bosses that are in the middle of an attack animation.
- Sticky
>Sets Movement Speed and Jump Height to 25%.
>Stacks last for x seconds.
- Weakened
>For Players: Reduces all sources of damage dealt by 75%,
>For Enemies: Reduces all sources of damage dealt by 25%.
>Stacks last for 0.8 seconds
- Bleeding
>Deals Physical damage when a stack expires.
>Stacks last for 0.8 seconds.
- Burning
>Deals Fire damage when a stack expires.
>Stacks last for 0.5 seconds.
- Hemorrhaged
>Deals Physical Damage when a stack expires, and at double the damage amount of Bleeding.
>Stacks last for 0.8 seconds.
- Poisoned
>Deals Poison damage when a stack expires.
>Stacks last for 0.75 seconds.
- Apply Force
>Spendable for the Fistmage: Apply Force Upgrade
- Collapse
>Deals 10% of your HP every 0.1 seconds, it will constantly reapply if the collapse timer has passed the limit.
- Dead
>Out of action, but revivable. Inflicts Mortal Curse when revived.
- Mortal Curse
>You cannot be revived again if you die. This can be bypassed with  Thaumaturge: Everlife.
- Revive Protection
>Grants 2-5 seconds of damage protection once revived.
- Stop and Go
>Swaps between STOP and GO. See  Way of the Law for more information.
- Vital
>Indicates when  Healthy Guard is active.
- Volatile/易爆
>Allows you to survive an instance of damage and leaves you at 1 HP, as long as you were not LOW HP to begin with.

## Runes + Curses
### Runes
#### Introduction
>Runes are powerful upgrades you can carry into a run. You need to fully complete the game once to randomly unlock a rune. You equip them at the Workshop Anvil in the starting hall.  
><br>There are four rune slots in total, but the first rune only activates at the Penumbral stage. Each subsequent slot activates at a later stage, up to Eclipse.  
>As of the Patreon Playtest Demo, only the Penumbral and Antumbral slots are usable.  
><br>Runes are strong, but each slot comes with a random rune curse when activated, and you can get the same curse more than once. The Penumbral slot gives 1 layer of curse, the Antumbral slot gives 2 layers, and so on.</br>
#### Runes List
- Focus Growth
>Critical Strike Chance +10% (+10% for each phase).
- Cleansing Growth
>Gain a resistance to all negative status effects (increases resistance each phase).
- Recovery Growth
>Utility Cooldown -20% (-20% for each phase).
><br>Can prevent Runic Curse: Asthma</br>
- Power Growth
>Damage +10% (+10% for each phase).
><br>Can prevent Runic Curse: Hollow</br>
- Dexterity Growth
>Attack Speed +30% (+30% for each phase).
><br>Can prevent Runic Curse: Atrophy</br>
- Precision Growth
>Critical Strike Damage +25% (+25% for each phase).
- Health Growth
>Max HP +25 (+25 for each phase).
><br>Can prevent Runic Curse: Drain</br>
- Satiety Growth
>Healing Received +20% (+20% for each phase).
><br>Can prevent Runic Curse: Hypoxia</br>
- Defense Growth
>Defense +10% (+10% for each phase).
><br>Can prevent Runic Curse: Shedding</br>
- Rejuvenating Growth
>Health Regeneration +200% (+200% for each phase).
><br>Can prevent Runic Curse: Anemia</br>
- Skybound
>Extra Jump +1 (+1 for each phase).
>Jump Height +25% (+25% for each phase).
><br>Can prevent Runic Curse: Sloth</br>
- Way of the Turtle
>Max HP +40 (+40 for each phase).
>Defense +15% (+15% for each phase).
>Movement Speed -20% (-20% for each phase).
><br>Can prevent Runic Curse: Drain</br>
- Active Guard
>Using your Utility Skill has a 5% chance to grant you the RESILIENCE status effect (+2% for each phase).
><br>Can prevent Runic Curse: Violet</br>
- Manic Gambit
>Any sacrificed Artifact will grant you 300% of its stats (+100% for each phase).
>You will only get 1 Token in every stage.
- Big and Greedy
>Chance to find an extra Token +20% (+15% for each phase).
>If successful, have a 50% chance to find another extra Token.
>On activation, suffer from a more potent Runic Curse.
- Big and Needy
>Chance to refund your Token after purchasing a COMMON upgrade +17% (+4% for each phase).
>On activation, suffer from a more potent Runic Curse.
- Big and Picky
>Gain 1 extra option when choosing an upgrade.
>Gain 1 extra re-roll when choosing an upgrade (+1 re-roll for each phase).
>On activation, suffer from a more potent Runic Curse.
- Big and Insured
>Receive 1 Token (+1 for Antumbra or above phases).
>Gain 1 extra re-roll when choosing an upgrade (+1 for each phase).
- Precise Shot
>Projectile Speed: +35% (+35% for each phase).
>Projectile Distance +10 M (+10 M for each phase).
>Projectile Spread -2% (-2% for each phase).
><br>Can prevent Runic Curse: Tremor</br>
- Stalwart Will
>Defense +20% (+20% for each phase).
>Damage -10% (-10% for each phase).
><br>Can prevent Runic Curse: Shedding</br>
- Way of the Rabbit
>Jump Height +30% (+30% for each phase).
>Movement Speed +15% (+15% for each phase).
>Defense -10% (-10% for each phase).
><br>Can prevent Runic Curse: Sloth</br>
- Mark of Pusciel
>For each second without dealing damage gain +2.5% Damage, up to 10 seconds (+2.5% for each phase),
>Attack Speed: -20% (-20% for each phase)
><br>Can prevent Runic Curse: Hollow</br>
- Wrathful Binding
>Heal 2 HP upon dealing damage. (+2 HP for each phase),
>Damage: +5% (+5% for each phase),
>Attack Speed: +5% (+5% for each phase),
>Chance to inflict all status effects: +10% (+10% for each phase).
>Your HP will decay by 5 every 2 seconds while not dealing damage (-5 HP for each phase).
>Taking damage will inflict you with a brief DECAYED Status Effect (Increased duration for each phase)
><br>Can prevent Runic Curse: Hollow</br>

### Curses
- Fragility
>-15% PHYSICAL Defense per stack
- Smolder
>-15% FIRE Defense per stack
- Fever
>-15% FROST Defense per stack
- Conductor
>-15% ELECTRIC Defense per stack
- Profane
>-15% LUMINOUS Defense per stack
- Divine
>-15% SHADOW Defense per stack
- Rot
>-15% POISON Defense per stack
- Tremor
>+4% Projectile Spread per stack
- Drain
>-15 Maximum HP per stack
- Shedding
>-11.5% Overall Defense per stack
- Anemia
>-150% Health Regeneration per stack
- Hypoxia
>-20% Healing Received per stack
- Light
>+15% increased Knockback per stack
- Asthma
>+20% Utility Cooldown per stack
- Violet
>Attacks inflicted towards you has a small chance to be a PURPLE attack. +15% Chance per stack
- Hollow
>Your attacks have a chance to deal zero Damage (this also applies to DoTs). +5% Chance per stack
- Propellant
>-35% Projectile Speed per stack.
- Friction
>-X M Projectile Distance per stack.
- Atrophy
>-20% Attack Speed per stack
- Sloth
>-8% Movement Speed and -10% Jump Height per stack.

## Artifacts
### Introduction
>Artifacts are a key form of progression in Ecliptica, they serve as an extra task to do before you can fight the boss on each floor.
><br>Artifacts held actually dictates what Map you go to next.</br>
>Each Artifact can give stat bonuses to everyone for the troubles of bringing them to the dimensional teleporter.
><br>If an Artifact is the last objective before gathering to the Dimensional Teleporter, everyone will be granted the Haste Status Effect until one is successfully sacrificed to the Dimensional Teleporter.</br>

### Artifact List
- Encrypted Archive
>Utility Cooldown -5%,
>Movement Speed +5%
- Goblet of the Sun
>LUMINOUS Damage +8%,
>SHADOW Defense +8%
- HC Armor Plating
>PHYSICAL Defense +7%
- Heart of Cinders
>ELEMENTAL Defense +6%
- Essence of Malice
>SHADOW Damage +6%,
>LUMINOUS Defense +6%
- Wheel of Reincarnation
>Received Healing +3%,
>Maximum HP +5
- Sealed Megium
>Damage +3%
- SparkGate Fragment
>Attack Speed +8%,
>Projectile Speed +20%

### Artifacts and Final BOSS
- When the most sacrificed artifact is **HC Armor Plating**, the final boss is **Jim C. Bringer**
- When the most sacrificed artifacts are **Essence of Malice (Mainly), Encrypted Archive, Sealed Megium, SparkGate Fragment**, the final boss is **Gilgamesh**

## Maps
>Except for functional maps (Beginning Lobby, The End of Time) and final maps (Altar of Destruction, Ground Zero, Bringer's Desert, Bringer Mothership) where artifacts don't spawn, as well as the Hall of Beginnings, artifacts in all other maps spawn randomly. Sometimes only one artifact appears, and sometimes all of them show up.
- Beginning Lobby
>You’ll come to this map when entering the game, wiping out the team, or when the game ends; it’s not a combat area.
- Hall of Beginnings
>The first stage always starts on this map, and all artifacts will definitely spawn.
- Geometric Citadel
- Copied City
- GM_Func_Flat
- GM_Func_Flat_3
- GM_CarCon
- GM_BigCity
- GM_BigCity2
- Proto Colony
- Balboa Ruins
- Lost Elysia
- Calamity Palace
- Hallow
- Calamity Palace 2
- Outer Heaven
- Halram Mines
- VRChat Hub
- Altar of Destruction
>This map is entered when the final boss is Gilgamesh.
- Ground Zero
>When Gilgamesh enters the third phase, players will enter this map
- Bringer's Desert
>This map will be accessed when the final boss is Jim C. Bringer.
- Bringer Mothership
>This map will appear when Jim C. Bringer enters the third stage.
- The End of Time
>After the player defeats the final boss, they will enter this map, where they can check some information related to the current battle. Players need to gather at the black hole to reset everything and return to the Beginning Lobby.