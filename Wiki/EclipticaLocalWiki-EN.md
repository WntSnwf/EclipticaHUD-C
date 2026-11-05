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
10. [Bosses](#bosses)


## The flow of a round
1. Choose your class in the Beginning Lobby and equip runes at the Workshop Anvil.  
2. Enter the map (determined by the artifact carried from the previous stage) and clear enemies and bosses stage by stage.  
3. At the end of each stage, sacrifice your artifact and challenge the boss; after defeating it, move on to the next stage.  
4. Between stages, enter the In-Between, and use tokens to buy upgrades from three Vendors.  
5. Stage progression: every time you go through a shop, the phase wheel advances, changing the difficulty and enemy composition.  
6. Finally, face the final boss at the Eye of the Eclipse.

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
   >“Decayed” — prevents healing, all recovery methods stop working.
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
>When applying the BLEEDING Status Effect to an enemy with the effect already applied, convert all cumulative stacks into the Hemorrhaged Status Effect.
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
10% chance to inflict Frozen status effect.
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
Twinmage is a really interesting class, with unique skill mechanics and gameplay. By choosing different elemental hand skills, players can adjust their damage output according to personal preference and tactical needs. Personally, I recommend a combination of the Electric Hand and any other elemental hand, then choose either the left or right path upgrade based on the Electric Hand's left and right hand bonuses. Almost all upgrades are core upgrades, and there are also some general upgrades you need to pick. I recommend it for new players.
#### Recommended Upgrades
See [Twinmage.png](./Twinmage.png)

### Gunmancer
#### Introduction
With enough cybernetic enhancements and a brain-interfaced Blast Cannon, anyone can become a Sorcerer these days.
#### Skills
>Gunmancer's Primary and Secondary skills both have options, and you can choose different skills to change the effects, but each skill can only be chosen once.
##### primary skill: VA-11 Blast Cannon
Fire a long-range hit scan attack every 2 seconds which deals 50 ELECTRIC Damage.
Additionally, apply a small explosion where your attack hits, dealing 50% of the projectile's Damage.
Has an 15% chance to apply the PARALYZED debuff to enemies.
##### Primary skill: Kinetic Flechette
Fire a long-range projectile dealing 50 PHYSICAL Damage. The projectile can pierce an enemy, then redirect towards the nearest enemy.
15% Chance to inflict the BLEEDING status effect.
##### Secondary skill: Firebomb
Launch an explosive projectile with high gravity every X seconds which deals 50 FIRE Damage.
This attack explodes in a wide radius when it hits, dealing 100% of the projectile's Damage.
##### Secondary skill: Photon Condenser
Fire fast bullets every 0.25 seconds which deals 10 LUMINOUS Damage.
5% Chance to inflict the WEAKENED status effect.
##### Secondary skill: Antimatter Accelerator
Fire a scattered blast of five projectiles every X seconds which each deal 8 SHADOW Damage. Hold to narrow the spread.
5% Chance to inflict the BREACHED status effect.
##### Utility skill: Airblast
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
After the v0.6 update, Gunmancer got a small buff, especially the Kinetic Flechette, which was significantly improved. A turning mechanism was added, making it perform better in group fights. Also, Gilgamesh’s second-stage hitbox is very small and it’s very... twitchy ~~(god of ADHD)~~, so the Kinetic Flechette’s tracking can handle it pretty well. Recommended for new players.
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
The editor has tried both of its modes: Jump Smash is better suited for players with some gaming experience, while Chuck is more for beginners. But what they have in common is that they struggle against moving targets. In the current version, where ADHD-like behavior is pretty common, they're a bit at a disadvantage. Still, Spellhammer's single-hit damage is quite impressive.
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
- Shield Mage: Unbreakable
>Damage received from PURPLE Attacks -5%,
>Damage received from PURPLE Attacks with an active Evasive Maneuver Shield -10%
- Shield Mage: Bulldozer
>Using your Evasive Maneuver Dash will deal FROST Damage in its direction, and knock enemies back.
- Shield Mage: Ice Burst
>Increases charge-up power of Ice Burst for each blocked Attack
- Shield Mage: Mastery
>Increase the size of your Evasive Maneuver shield by X% (X% per stack)
- Shield Mage: Drainshield
>Blocking Damage in your Defensive Stance Heals 5 HP (+3 HP per stack),
>Health Regeneration -100% (-100% per stack)
- Shield Mage: Rally Up
>Using your Evasive Maneuver Shield gives you and your allies around you a brief EMPOWERED status effect
- Shield Mage: Warden
>Using your Evasive Maneuver Shield gives you and all your allies the RESILIENCE status effect, letting them block an instance of Damage,
>Utility Cooldown +50% (+50% per stack)
#### Editor's Note
The editor hasn't played Shield Mage, so can't give a very fair evaluation, but the importance of a shield to a team is obvious, and it's easy to use, though its damage output isn't high.

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
>Reduce number of stacks taken of the Frozen status effect by X (X per stack).
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
>Shadow damage can apply this debuff.
- Decayed
>Sets healing received to 0%
>Stacks last for X seconds.
- Frozen
>Each stack deals frost damage when it expires, lasting 0.6 seconds. Each stack has a chance to inflict 'Freeze': movement speed -75%; player's Utility Skill cooldown rate -90%.
>Frost damage can apply this debuff.
- Heavy
>Sets jump height to 0%。
>Stacks last for X seconds
- Paralyzed
>Each stack deals lightning damage when it expires, lasting for 0.3 seconds per stack. Each stack also has a chance to apply 'Rigid': movement speed -99% and unable to attack. It won't interrupt enemies or bosses that are in the middle of an attack animation.
>Electric damage can apply this debuff.
- Sticky
>Sets Movement Speed and Jump Height to 25%.
>Stacks last for x seconds.
- Weakened
>For Players: Reduces all sources of damage dealt by 75%,
>For Enemies: Reduces all sources of damage dealt by 25%.
>Stacks last for 0.8 seconds
>Luminous damage can apply this debuff.
- Bleeding
>Deals Physical damage when a stack expires.
>Stacks last for 0.8 seconds.
>Physical damage can apply this debuff.
- Burning
>Deals Fire damage when a stack expires.
>Stacks last for 0.5 seconds.
>Fire damage can apply this debuff.
- Hemorrhaged
>Deals Physical Damage when a stack expires, and at double the damage amount of Bleeding.
>Stacks last for 0.8 seconds.
- Poisoned
>Deals Poison damage when a stack expires.
>Stacks last for 0.75 seconds.
>Poison damage can apply this debuff.
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
>Taking damage will inflict you with a brief Decayed Status Effect (Increased duration for each phase)
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
>Artifacts are a key form of progression in Ecliptica, they serve as an extra task to do before you can fight the boss on each stage.
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

## Bosses
### Boss list
- [Maxipuss](#maxipuss)
- [Darkmouth](#darkmouth)
- [Kakarot](#kakarot)
- [NaN](#nan)
- [Beelzebub](#beelzebub)
- [Buff Noob](#buff-noob)
- [Vesra](#vesra)
- [Pride](#pride)
- [Steven](#steven)
- [Kodama](#kodama)
- [The Gravetender](#the-gravetender)
- [The Black Lily](#the-black-lily)
- [Zaveah](#zaveah)
- [Middleman](#middleman)
- [Ha'Kli](#hakli)
- [Amaziah](#amaziah)
- [Jacked O' Lantern](#jacked-o-lantern)
- [M-41-D](#m-41-d)
- [Corus](#corus)
- [Yuki](#yuki)
- [Cone Head](#cone-head)
- [Mephiel](#mephiel)
- [Golden Grouch](#golden-grouch)
- [Pandora](#pandora)
- [Abaddon](#abaddon)
- [Khepri](#khepri)
- [Onyx Pilot](#onyx-pilot)
- [Bravera](#bravera)
- [O-One](#o-one)
- [Neo Pilot](#neo-pilot)
- [Jim C. Bringer](#jim-c-bringer)
- [Gilgamesh](#gilgamesh)

### Prime
#### Maxipuss
##### Base stats
- Base HP: 5300
>Base HP is the value when only 1 player is in the instance and the boss spawns on the first layer (uncertain)
- Phases: 1
>Sub-phases driven by an HP threshold are not counted; only Phase1/2/3 as explicitly labelled in the game log
- Weak to: Frost, Shadow
- Resists: Luminous
##### Damage types
- Deals Physical damage
- Can apply Poisoned
>Debuffs that come with a damage type are not repeated under "can apply"
##### Behavior
- The Maxipuss fight has 1 phase.
- Up close, Maxipuss uses simple punches and an opening grab.
- Against distant targets, Maxipuss may throw a furball or jump.
##### Editor's note
A very simple boss; there is nothing in particular to watch out for.

#### Darkmouth
##### Base stats
- Base HP: 4200
- Phases: 1
- Weak to: Shadow, Poison
- Resists: Luminous
>Editor's rant: Luminous is almost universally resisted — nearly every enemy resists it, and enemies weak to Luminous are very rare.
##### Damage types
- Deals Physical and Poison damage
##### Behavior
Darkmouth tries to keep its distance and uses 2 attacks. The first is a volley of poison projectiles; the second is a charge at the target that deals noticeably higher damage. It usually alternates between the two, but occasionally changes up the pattern and timing to catch opponents off guard.
##### Editor's note
Darkmouth is slightly harder than Maxipuss and can put some pressure on a solo run, but in multiplayer it is still just a speed bump.

#### Kakarot
##### Base stats
- Base HP: 5800
- Phases: 1
- Weak to: none
- Resists: none
##### Damage types
- Deals Physical damage
##### Behavior
- The Kakarot fight has 1 phase.
- Kakarot alternates between a heavy forward smash and scattering small AoEs around itself.
- Against distant targets, Kakarot may throw rocks or jump upward with low accuracy.
##### Editor's note
Kakarot is easier than Darkmouth but slightly harder than Maxipuss; it adds a little pressure in solo play, but in multiplayer it is still a speed bump.

#### NaN
##### Base stats
- Base HP: 5300
- Phases: 1
- Weakness and resistances: depend on the current mode, see Behavior
##### Damage types
- Deals Fire, Frost, Electric, Luminous and Shadow damage
##### Behavior
- NaN is a machine that can switch between 4 different modes, each with its own difficulty and weakness.
- In Fire mode, NaN becomes weak to Fire and periodically fires projectiles at the target, with a chance to ignite it.
- In Frost mode, NaN becomes weak to Frost and fires grouped projectiles, with a chance to freeze the target.
- In Electric mode, NaN becomes weak to Electric and fires lightning into the sky, which then lands in a small AoE with a chance to paralyze the target.
- In Shadow and Luminous modes, NaN can fire a ring of shadow projectiles that apply BREACHED, or a row of luminous projectiles that apply WEAKENED. Note that in this form it is not weak to Shadow or Luminous, because it uses both opposing elements at once.
##### Editor's note
NaN is relatively easy, though still harder than Maxipuss. In solo play the various debuffs are unpleasant if you do not dodge properly; in multiplayer it is still a speed bump.

#### Beelzebub
##### Base stats
- Base HP: 5200
- Phases: 1
- Weak to: Fire, Shadow
- Resists: Frost, Luminous, Poison
##### Damage types
- Deals Physical and Poison damage
- Can apply Decayed
##### Behavior
- The Beelzebub fight has 1 phase.
- Beelzebub can summon flies to fight alongside it. They spawn automatically when its HP drops to 50%.
>Note: even if Beelzebub itself is killed, the summoned flies remain, and the layer cannot be cleared until all of them are dead. The same rule applies to every boss that summons minions and will not be repeated below.
##### Editor's note
Beelzebub itself is not hard, but the flies it summons are annoying and harass you constantly — even in multiplayer.

#### Buff Noob
##### Base stats
- Base HP: 4800
- Phases: 1
- Weak to: Electric, Shadow
- Resists: Luminous
##### Damage types
- Deals Physical damage
##### Behavior
The Buff Noob fight is the first to introduce purple attacks, in the form of heavy slams that pierce the opponent's defense. He focuses on closing in and knocking the opponent down with consecutive hits. At around 40% HP he consumes one of two items, Pizza or Bloxy Cola, healing himself and gaining ENFORCED or EMPOWERED respectively. When the threshold is reached again he repeats this with the remaining item.
##### Editor's note
Buff Noob is not hard — honestly easier than Beelzebub. Its purple attacks are easy to dodge; the hit window is just long, so do not walk into range before the animation ends.

### Late Prime / Early Penumbra
#### Vesra
##### Base stats
- Base HP: 4800
- Phases: 1
- Weak to: Fire, Shadow
- Resists: Frost, Luminous, Poison
##### Damage types
- Deals Physical damage
##### Behavior
- The Vesra fight has 2 sub-phases: a normal form and a cocoon form. While in the cocoon, Vesra is immune to all damage.
- In the normal form, Vesra alternates between a ground moveset and an air moveset. At 50% HP it enters the cocoon, spawns one Peltapod Guard and then spawns ordinary Peltapods at fixed intervals. Once the Peltapod Guard is killed (uncertain), it leaves the cocoon and returns to the normal form.
##### Editor's note
Vesra is not hard; with good spacing and positioning you can clear it without taking damage. Note that while flying it raises its large arms, which blocks damage in some areas.

#### Pride
##### Base stats
- Base HP: 4600
- Phases: 1
- Weak to: Electric
- Resists: Luminous, Shadow
##### Damage types
- Deals Physical and Luminous damage
##### Behavior
- Pride focuses on controlling the area around itself rather than a single target. Many of its attacks spawn heart projectiles that orbit it while it performs a move and catch opponents off guard. It can also cast 2 different beams: one summoned in front of it, and one from its umbrella.
- Pride can take to the air at any moment, spawning a swarm of heart projectiles and firing more of them at opponents on the ground, following them at close range.
##### Editor's note
Pride is one of the more peculiar bosses players meet early on. Most of its attacks are not very threatening, but the heart projectiles and the WEAKENED they apply are annoying. While flying, its umbrella blocks damage in some areas.

### Penumbra
#### Steven
##### Base stats
- Base HP: 8600
- Phases: 1
- Weak to: Frost, Shadow
- Resists: Fire, Luminous
##### Damage types
- Deals Physical and Fire damage
##### Behavior
- The Steven fight has 2 sub-phases: a normal form and a burning form.
- In the normal form, Steven delivers high-damage slashes and lays down syrup pools. Standing in syrup stacks the Sticky debuff.
- At 50% HP, Steven enters the burning state: every move gains extra fire damage and a chance to inflict Burning. His syrup moves also fire out more syrup pools.
##### Editor's note
Steven is another peculiar boss; the syrup pools it drops are genuinely annoying, especially in the second sub-phase — on smaller maps you will find syrup everywhere and simply have to eat the Sticky slow. Note that Steven fires fast projectiles at distant targets, so do not assume it is a pure melee boss.

#### Kodama
##### Base stats
- Base HP: 6500
- Phases: 1
- Weak to: Luminous
- Resists: Physical
##### Damage types
- Deals Shadow damage
- Can apply Decayed, Bleeding and Heavy
##### Behavior
Kodama is a stationary boss with a ring of shadow around the arena that deals continuous damage. It uses large AoE blasts and summons thorns for purple attacks.
##### Editor's note
Kodama is another peculiar boss. Being immobile makes it a training dummy, but its blasts and spinning laser constantly interrupt your damage. Some classes can jump onto its back to avoid the blasts and laser, though that may not avoid the thorns.

#### The Gravetender
##### Base stats
- Base HP: 6500
- Phases: 1
- Weak to: Luminous, Frost
- Resists: Fire
##### Damage types
- Deals Shadow and Physical damage
##### Behavior
- The Gravetender fight has 1 phase.
- The Gravetender is a semi-stationary boss that occasionally burrows under the arena to move beneath players. It sometimes fires a Gravity Well — a slow-moving sphere that pulls every player in its radius into it; Gravity Well cannot be killed and only disappears over time.
##### Editor's note
A pure training dummy — if it never moved it would be the perfect one. Gravity Well can be a little annoying. By the way, Gravity Well counts as a summon, so the layer cannot be cleared until it disappears.

### Late Penumbra / Early Antumbra
#### The Black Lily
##### Base stats
- Base HP: 6500
- Phases: 1
- Weak to: Fire, Frost
- Resists: Luminous, Shadow
##### Damage types
- Deals Luminous and Shadow damage
- Can apply Decayed and Bleeding
##### Behavior
The Black Lily is a stationary boss that can summon up to 3 Black Lily Tokens at any time. It starts with only 2 attacks; below 50% HP it gains several additional and far more destructive moves, from puddles that apply the Decayed status to a large laser that covers half the arena. Many of its attacks have almost no telegraph, forcing opponents to watch both it and its minions or be caught out.
##### Editor's note
A miserable fight. Even though it is stationary, its puddles and lasers force you to keep moving to find a safe spot, and the WEAKENED from its Luminous damage plus the ENFORCED it applies to itself make your damage feel like scratching.

#### Zaveah
##### Base stats
- Base HP: 16000
- Phases: 1
- Weak to: Electric, Shadow
- Resists: Fire, Luminous, Poison
##### Damage types
- Deals Physical and Electric damage
- Can apply Burning
##### Behavior + Editor's note
Zaveah uses a wide range of skills — from a spinning bumper car that drags players along, to projectile volleys, to the extending lance in its hand, to summoning a series of minions — forcing opponents to mind both their positioning and the minions. It has a fair amount of difficulty. Once its HP crosses certain thresholds its spinning skill is upgraded and becomes far more threatening.
>Minions it may summon include: Voltwall, Voltwalker, Volt Buster

#### Middleman
##### Base stats
- Base HP: 7800
- Phases: 1
- Weak to: Fire, Electric, Shadow
- Resists: Luminous, Poison
##### Damage types
- Deals Physical and Electric damage
##### Behavior
Middleman is the first fast-paced boss: it charges constantly and slashes with twin swords. During the fight it leaps high into the air and then either dives back down to kick or fires a piercing laser at the opponent. Middleman specialises in close quarters, and most of its attacks lunge at the opponent to close the gap quickly.
##### Editor's note
A relatively peculiar enemy — very mobile, and the Bleeding it applies is annoying — but not hard; a multiplayer party can usually clear it with no casualties.

### Antumbra
#### Ha'Kli
##### Base stats
- Base HP: 21000
- Phases: 1
- Weak to: Frost, Shadow
- Resists: Fire, Luminous
##### Damage types
- Deals Physical and Fire damage
##### Behavior + Editor's note
Ha'Kli, added in v0.6, is fairly difficult. It throws fireballs that deal wide-area damage, can summon moving fire pillars to disrupt players, and can apply ENFORCED and EMPOWERED to itself. Its damage is high, so keep dodging; even a multiplayer party will find it somewhat demanding.

#### Amaziah
##### Base stats
- Base HP: 15000
- Phases: 1
- Weak to: Frost, Shadow
- Resists: Fire, Luminous, Poison
##### Damage types
- Deals Physical and Poison damage
##### Behavior
Amaziah is a poison boss that fights mostly at close range, and every attack also fires poison projectiles. At 60% HP its moveset expands: it can make larger, deadlier jumps, lunge at airborne opponents, and fire a beam from its face.
##### Editor's note
Another miserable fight — mobile, high damage, DoT: the full package. It also has 50% Poison resistance, which lowers how fast Thaumaturge builds Life Energy and therefore how often it can heal. A party with low gear can easily wipe.

#### Jacked O' Lantern
##### Base stats
- Base HP: 18000
- Phases: 1
- Weak to: Fire, Shadow, Poison
- Resists: Frost, Luminous, Electric
##### Damage types
- Deals Physical and Fire damage
##### Behavior
- The Jacked O' Lantern fight has 2 sub-phases. In the second, all of its basic swings also fire additional fire projectiles, and all of its slams leave fire pillars behind.
- Jacked O' Lantern enters the second sub-phase at 35% HP and heals a large amount of its total HP. In that sub-phase it may also use Bulk Up, gaining ENFORCED and EMPOWERED for a long time.
##### Editor's note
Jacked O' Lantern is not hard to deal with, but the moves it gains in the second sub-phase — randomly throwing fireballs and leaving fire pits on the ground — are annoying, and its slams track you somewhat.

### Late Antumbra / Early Umbra
#### M-41-D
##### Base stats
- Base HP: 1300
- Phases: 1
- Weak to: Electric, Shadow
- Resists: Fire, Luminous, Poison
##### Damage types
- Deals Electric damage
##### Behavior
- The M-41-D fight has 2 sub-phases: a standard phase and a tower phase.
- Once only, at 40% HP, M-41-D summons 2 Disruption Towers. Each tower alternates between healing M-41-D and using a large electric AoE when players come close. After the phase change M-41-D also becomes stronger, and several moves gain radius.
##### Editor's note
M-41-D is not hard but very annoying: its wide AoEs do little damage yet are deeply insulting, and the Paralyzed procs and resulting stiffness make the fight uncomfortable.

### Umbra
#### Corus
##### Base stats
- Base HP: 12000
- Phases: 2
- Weak to: Frost, Shadow
- Resists: Fire, Luminous
##### Damage types
- Deals Fire damage
##### Behavior
- The Corus fight has two phases. In phase 1, every attack releases a continuous barrage of fireballs across the arena. He can also leap high and hurl a larger fireball down, leaving a fire pool on the ground that keeps damaging opponents.
- After his phase-1 death he enters phase 2. In that phase most of the fireballs he fires also leave fire pools covering the arena floor, and his jump attack leaves fire pillars that persist and grow over time. Together with the pools, Corus makes most of the arena hard to traverse, leaving players almost no room to dodge his chained attacks as he closes in.
##### Editor's note
A rather peculiar boss: high damage, area denial, DoT, very mobile — roughly on par with Amaziah, except that thankfully it has no Poison resistance. Even so, an under-geared party can still be wiped by its second phase.

#### Yuki
##### Base stats
- Base HP: 10000
- Phases: 2
- P1 weak to: Electric
- P2 weak to: Fire
- P1 resists: none
- P2 resists: Frost, Electric
##### Damage types
- Deals Physical and Frost damage
##### Behavior
- The Yuki fight has 2 phases: a ground phase and a flight phase.
- In phase 1, Yuki tries to punch and grab players. At 50% HP Yuki can slam the ground and release a purple shockwave.
- In phase 2, Yuki stays airborne permanently and gains ranged ice attacks. At 50% HP Yuki unlocks its full moveset, can split parts of the arena off with ice walls, and can use a devastating spray attack.
##### Editor's note
The only (uncertain) non-final boss that switches weaknesses and resistances by phase. Not hard, but very mobile, especially in phase 2. Watch the ice walls: do not try to cross them at low HP, because they deal continuous Frost damage to players who attempt it.

#### Cone Head
##### Base stats
- Base HP: 20000
- Phases: 2
- Weak to: Shadow
- Resists: Luminous
##### Damage types
- Deals Physical damage
##### Behavior
- Cone Head's main moveset uses a traffic-light mechanic: move on green, stop on red, to dodge his attacks. In phase 1 he attacks with one of three swords, occasionally teleports behind the opponent, or covers most of the arena with a traffic-light attack. Failing to follow the rule deals devastating damage. At around 30% HP the sword flies from his hand and he enters a melee sub-phase, chasing and punching the opponent until defeated.
- After phase 1 is beaten he enters phase 2, draws the remaining two swords and uses the traffic-light mechanic to the full. Every slash is now red or green, dodged by not moving or by moving respectively. His large traffic-light AoE now hits 3 times, forcing opponents to memorise the light order or take heavy damage.
##### Editor's note
A "cat lover" and the nemesis of Nekomancer. The traffic-light mechanic usually kills the cats Nekomancer summons, especially in phase 2, where the traffic-light AoE typically clears the field of cats. Other classes that respect the mechanic will not find it hard.

### Late Umbra / Early Eclipse
#### Mephiel
##### Base stats
- Base HP: 19000
- Phases: 2
- Weak to: Luminous
- Resists: Electric
##### Damage types
- Deals Shadow damage
- Can apply Bleeding
##### Behavior
- The Mephiel fight has 2 phases. Phase 2 greatly expands the moveset and strengthens earlier moves.
- Mephiel is a bullet-hell style boss that covers the arena with large numbers of danger zones. In phase 2 Mephiel gains flight, forcing players to focus on surviving for a while rather than damaging the boss.
- Mephiel has a powerful spinning pizza-cutter move that requires players to circle around it.
##### Editor's note
All damage and no mechanics — and plenty of damage (PS: unless you count the spinning cutter as a mechanic). A hard boss whose wide range and high damage can easily wipe a party.

#### Golden Grouch
##### Base stats
- Base HP: 18500
- Phases: 1
- Weak to: Fire, Luminous
- Resists: Frost, Electric, Poison
##### Damage types
- Deals Physical and Shadow damage
- Can apply Decayed, Frozen and Heavy
##### Behavior
- The Golden Grouch fight has 2 sub-phases, i.e. stances: sword stance and bare-handed stance. The two have completely different movesets. Once per fight, when Golden Grouch drops below 70% HP, his sword is knocked away and he switches to the bare-handed stance. The sword stays next to the Gate as a passive entity. In the bare-handed stance Golden Grouch can use a move that summons 6 Shadow Grouch enemies; that move can be used at most twice.
- Shadow Grouch HP decays, losing 3% of its max HP per second. Every 10 seconds each Shadow Grouch grants Golden Grouch a brief INVINCIBLE status effect.
- Below 40% HP in the bare-handed stance, Golden Grouch starts running for the dropped sword, picks it up and switches back to the sword stance. In the sword stance, below a certain HP he gains an expanded moveset.
##### Editor's note
Not an easy boss. The INVINCIBLE it gains in the bare-handed stance plus the string of debuffs from its occasional floor-AoE attacks are quite annoying, and once it re-enters the sword form it can also release wide purple attacks that you must dodge promptly.

### Late Umbra
#### Pandora
##### Base stats
- Base HP: 24000
- Phases: 1
- Weak to: Fire, Luminous
- Resists: Frost, Electric, Shadow
##### Damage types
- Deals Physical and Frost damage
##### Behavior
- Pandora is a flying boss that attacks with large ice AoEs and fast dash attacks. It can create waves of ice shards that must be jumped over, and fires ice lasers horizontally across the arena.
- Above 50% HP it becomes more aggressive, using larger and more destructive attacks and sweeping across the sky at high speed to release bigger, defence-piercing ice bursts.
##### Editor's note
Another fairly hard boss. The large AoEs, lasers and ice storms are very hard to handle, and an under-geared party may be wiped.

### Eclipse
#### Abaddon
##### Base stats
- Base HP: 32000
- Phases: 2
- Weak to: Luminous
- Resists: Frost, Electric, Fire, Poison
##### Damage types
- Deals Physical and Shadow damage
- Can apply Decayed and Heavy
##### Behavior
- Abaddon is a huge Manalyte that summons up to 3 Elder Manalytes to fight alongside it. It casts large AoE attacks that create fire pillars and fireballs, as well as dark spheres that apply Decayed to opponents.
- After its phase-1 death, Abaddon sheds its skin and enters phase 2. The maximum number of Manalytes it can summon rises to 6. Most of its attacks now pierce the opponent's defence and have a larger radius. Its most destructive move is a shockwave that engulfs most of the arena.
##### Editor's note
A pure stat-check. It can hold its own against the final boss [Jim C. Bringer](#jim-c-bringer), and in fact many of its moves are similar, with similar resistances too. A boss to take seriously.

#### Khepri
##### Base stats
- Base HP: 26000
- Phases: 2
- Weak to: Fire, Shadow
- Resists: Frost, Luminous
##### Damage types
- Deals Physical and Frost damage
##### Behavior
- The Khepri fight has 2 phases. In phase 2 Khepri gains greatly increased mobility and flight.
- Khepri can release powerful pizza-cutter shaped ice attacks, which can chain up to 3 times. If players stay far away in phase 1, it throws extremely accurate ice spikes that always apply Frozen.
- In phase 2, if players approach Khepri it may choose to scream. Everyone inside the purple radius is applied Frozen, and it immediately takes flight. While flying, Khepri can both grab players and throw out tearing spreads of ice projectiles, all of which apply a long Frozen.
##### Editor's note
Another stat-check, and very mobile. Easily wipes a party.

#### Onyx Pilot
##### Base stats
- Base HP: 24000
- Phases: 1
- Weak to: Fire, Shadow
- Resists: Electric, Luminous
##### Damage types
- Deals Physical damage
##### Behavior + Editor's note
- Most of Onyx Pilot's attacks are ground slams or kicks, and the slams also create stone pillars that deal purple damage. Once its HP falls below a certain value, Onyx Pilot restores a large amount of HP (up to 5 times) and upgrades its slam, summoning more stone pillars.
- A pure HP wall: the health bar you see may be only half of what you actually have to chew through, but its overall threat is not high.

### Late Eclipse
#### Bravera
##### Base stats
- Base HP: 28000
- Phases: 2
- Weak to: Fire, Poison
- Resists: Frost, Luminous, Electric
##### Damage types
- Deals Physical and Electric damage
##### Behavior
- The Bravera fight has 2 phases. In phase 1 Bravera spawns together with 2 Opton Guards. The Opton Guards seek out the player with the lowest HP in the lobby and harass them continuously. Damaging Bravera does not require killing the guards, so the party decides who to attack.
- In phase 1, when Bravera reaches 50% HP he unlocks 2 new moves. He can now use Corkscrew Leap to cross long distances, and may end a dash with a heavy single-hit Pizza-cutter.
- Once phase 2 begins, Bravera unlocks a new moveset. It is far more agile than phase 1 and includes intense melee combos and dash abilities, making it hard to escape Bravera without support from teammates. In phase 2, at 50% HP, Bravera can use an upgraded version of the earlier Pizza-cutter: it now hits twice and can be used at any moment.
##### Editor's note
Another stat-check: high damage and strong harassment. Easily wipes a party.

#### O-One
##### Base stats
- Base HP: 16000
- Phases: 1
- Weak to: Frost, Shadow
- Resists: Luminous
##### Damage types
- Deals Physical damage
- Can apply Paralyzed
##### Behavior
- The O-One fight has two sub-phases.
- In the first sub-phase he uses a small battle axe and a pistol. He usually circles the opponent while shooting, occasionally dashing in to strike with the axe. He mostly repeats the loop of "shoot from range" and "fast close-range slash".
- At 40% HP he swaps weapons for a single sword and attacks at close range with higher speed and new attacks.
##### Editor's note
Not hard; apart from being very mobile there is little to complain about. In the "all-star" Late Eclipse phase he looks rather plain.

#### Neo Pilot
##### Base stats
- Base HP: 27000
- Phases: 1
- Weak to: Fire, Shadow
- Resists: Luminous, Electric
##### Damage types
- Deals Physical and Electric damage
- Can apply Heavy
##### Behavior
- The Neo Pilot fight has 2 sub-phases. If players take to the air while fighting Neo Pilot, she leaps at them and tries to kick twice. Those kicks have a chance to apply the Heavy status effect.
- In her normal state Neo Pilot uses slashes and sidesteps. Above 70% HP she starts jumping at players from long range.
- Once per fight, at 40% HP, Neo Pilot enters sub-phase 2. She heals a large amount of HP and attaches an electric shockwave to all of her jumps, which players must jump over to dodge. Her melee attacks also gain a significant speed increase. At 40% HP again, she unlocks two powerful new moves: the first is a near-instant front-facing tankbuster that requires players to keep their distance; the second is a fast three-hit pizza-cutter.
##### Editor's note
A miserable fight. The shockwaves in the second sub-phase are annoying and hit hard. Easily wipes a party.

### Eye of the Eclipse
#### Jim C. Bringer
##### Base stats
- Base HP: 50000
- Phases: 3
- Weak to: none
- P1 resists: none
>P2 is immune to all damage, see Behavior
- P3 resists: Elemental
##### Damage types
- Deals Physical damage
##### Behavior
**All of Jim's direct melee attacks deal PURPLE damage!**
- Phase 1: In phase 1 Jim is neutral to every damage type. His punches are strong and long-ranged, and he ignores any aggro ability, because his target is completely random across every phase of the fight. At 70% HP Jim unlocks more moves, including long-distance jumps and the notorious powerful laser. At 40% HP Jim can cast Cataclysm, a long channelled near-arena-sized nuke. Standing inside the centre radius of Cataclysm kills instantly, but the further you are from the centre the less damage you take. After casting Cataclysm he is passive for a long time, so use that window to heal the party and revive dead players.
>At 70%, 50% and 30% HP Jim pauses and summons a Jim's Wedge, a powerful support enemy that fires from long range.
- Phase 2: When phase 2 begins Jim climbs into Flipper MK.II Abyssal and stays inside for the whole phase. Flipper is immune to all damage and treats any damage as Blocked. It has 3 moves: ramming players at extremely high speed for heavy purple damage; deploying Jim's Wedge; and firing rocket barrages at the target from any distance.
>After 2 minutes, 4 Signal Towers land in the four corners of the arena. Players must stand inside these Signal Towers to charge them. Charging one alone takes 30 seconds, but that time increases with the number of players in the lobby. Multiple players under the same Signal Tower charge it faster. Once all 4 Signal Towers are charged, an orbital strike lands on Flipper and destroys it.
- Phase 3: Phase 3 consists of 2 sub-phases. Jim behaves like the original phase 1, but his entire moveset is strengthened. He swings faster, his combos are longer, and he unlocks extremely powerful combo finishers. Besides Physical, Jim now also gains 0.75x resistance to all elements.
>At 70% HP Jim unlocks the same moves as before, but strengthened again. His laser is wider and faster, and his jumps deal more damage. Jim can now also teleport next to distant players, or teleport mid-combo to catch players off guard.
><br>At 50% HP the second sub-phase begins. After a fairly long cooldown, a Product Barrel drops into the arena, landing directly opposite the side Jim is standing on. Jim becomes invincible and starts slowly jogging toward the barrel. Players must destroy it before he arrives. If Jim reaches the barrel he consumes it, healing a large amount of HP and gaining long-lasting ENFORCED and EMPOWERED buffs. If he heals above 50% HP this way, he cannot drop more barrels until the threshold is reached again. And in the second sub-phase Jim's moveset expands once more, unlocking powerful moves that often affect the entire arena.</br>
##### Editor's note
The perfect mix of stats and mechanics. As a final boss it applies plenty of pressure, and a low-gear party will not clear it easily.

#### Gilgamesh
##### Base stats
- Base HP: 70000
- Phases: 3
- Weak to: Fire, Luminous
- Resists: Frost, Shadow, Poison
##### Damage types
- Deals Physical, Electric and Shadow damage
- Can apply Heavy
##### Behavior
- Phase 1: Gilgamesh drives its spider legs into the arena, dealing purple damage in an area plus a slow shockwave covering the whole field; players must dodge both and then attack the legs. Gilgamesh also spits projectiles or calls lightning to disrupt your damage. In addition it slowly spits over the whole arena, which players must dodge in time.
- Phase 2: At the start of phase 2 Gilgamesh retreats off the field and a ladybug named Maurice spawns inside it. Maurice has a very small hitbox and many attacks; once players defeat Maurice, Maurice attacks Gilgamesh and Gilgamesh then enters phase 3.
- Phase 3: Phase 3 consists of two sub-phases. In the first, Gilgamesh uses most of its phase-1 skills — spider-leg slams, summoned lightning, projectile spit — and may also continuously pull players toward the centre of the field while damaging them. Gilgamesh also unlocks new skills, including extremely large AoEs and repeated spider-leg slams, all of which spawn shockwaves.
>After a while Gilgamesh leaves the field and continuously spawns small spiders inside it; players must clear them or they will interfere with later damage. After remaining outside for a while, Gilgamesh returns and releases a massive AoE together with a shockwave.
><br>When players empty Gilgamesh's health bar, Gilgamesh restores all of its HP and begins charging, entering the second sub-phase; players who are downed with Mortal Curse can now be revived normally. Players must kill Gilgamesh before the charge completes, or Gilgamesh wipes the party. In the second sub-phase Gilgamesh focuses on charging and only occasionally summons lightning to disrupt players, and no longer spawns shockwaves.</br>
##### Editor's note
A miserable fight. As a final boss it feels slightly lacking — especially the unexplained phase 2 and phase 3 — and the charge is effectively a DPS check. Jim has a similar design, but a forced wipe for low DPS is still criticised.