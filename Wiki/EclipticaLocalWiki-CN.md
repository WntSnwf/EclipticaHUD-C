# Ecliptica本地维基百科
**内容仅供参考，来源于[Ecliptica非官方中文wiki](https://ecliptica.xuemeng.work/)**

目录
1. [一局的流程](#一局的流程)
2. [相位](#相位)
3. [通用机制](#通用机制)
4. [Classes/职业](#classes职业)
5. [upgrades/通用升级](#upgrades通用升级)
6. [状态效果](#状态效果)
7. [符文与符文诅咒](#符文与符文诅咒)
8. [Artifacts/神器](#artifacts神器)
9. [Maps/地图](#maps地图)


## 一局的流程
1. 在 Beginning Lobby（起始大厅）选择职业，并在 Workshop Anvil（工坊铁砧）装备符文。
2. 进入地图（由本轮携带的神器决定），逐波清理敌人。
3. 每波之间进入 The In-Between（夹层空间），用代币在三位商人处购买升级。
4. 阶段推进：每经过一次商店，相位轮盘会前进，难度与敌人构成随之变化。
5. 本层结束时挑战 Boss；击败后进入下一层。
6. 把神器带到维度传送门献祭，最终在 Eye of the Eclipse 面对终局 Boss。

## 相位
| 相位值区间 | 阶段 | 英文名 |
| :---: | :---: | :---: |
| 0 < x < 0.2 | 初始相 | Primal |
| 0.2 < x < 0.4	| 半影 | Penumbral |
| 0.4 < x <0.6 | 伪本影 | Antumbral |
| 0.6 < x < 0.8	| 本影 | Umbral |
| 0.8 < x < 1 | 全蚀 | Eclipse |
| 1	| 蚀之眼 | Eye of the Eclipse |

## 通用机制
1. 部分 Boss 只在相位值达到阈值后才会出现，上表按「可能出现的最早阶段」排序。
2. PURPLE（紫色）攻击会无视你的防御，看到蓄力就立刻拉开距离。
3. 施加在 Boss 身上的状态效果效果会打折，但仍然生效。
4. 在 5 人以上的实例中成为最后一名存活者时，会获得 ADRENALINE（肾上腺素）状态效果。
5. 场地边界惩罚
   >Boss 战中，如果你贴着地图边界停留过久，会开始被持续施加两种负面状态：
   ><br>「中毒」效果 —— 约 10 点伤害/秒（按 100 点血量的基准估算）；</br>
   >「衰朽」效果 —— 无法被治疗，回血类手段全部失效。
   ><br>离开边界范围后，不会再继续施加这两种效果，但已经获得的 debuff 不会消失</br>
6. Token/代币
   >Token 是 Ecliptica 中用于升级的主要货币。
   ><br>每个关卡会在地图周围随机生成 3 个 Token。</br>
   >Token 的形状类似六角双锥。
   ><br>你会在商店中把 Token 花给三位商人。</br>
7. 玩家能造成的最高伤害会在6000后开始衰减。
8. 玩家与敌人能够造成的伤害分为PHYSICAL（物理）和ELEMENTAL（元素）两种，其中ELEMENTAL（元素）伤害包括：FIRE（火焰）、FROST（冰霜）、ELECTRIC（电击）、LUMINOUS（光耀）、SHADOW（暗影）和POISON（毒素）。且玩家只能造成普通伤害，敌人可以造成普通伤害和PURPLE（紫色）伤害。

## Classes/职业
>官方英文名/中文wiki命名/别称1、别称2、别称3
### 子目录
- [Spellsword/魔剑士](#spellsword魔剑士牢剑)
- [Twinmage/双生法师](#twinmage双生法师67)
- [Gunmancer/枪术师](#gunmancer枪术师枪炮师x光物火暗电枪)
- [Fistmage/拳法师](#fistmage拳法师拳师牢拳)
- [Spellhammer/咒锤战士](#spellhammer咒锤战士砸丢锤)
- [Shield Mage/盾法师](#shield-mage盾法师牢盾)
- [Thaumaturge/奇迹师](#thaumaturge奇迹师书奶)
- [Nekomancer/死灵猫使](#nekomancer死灵猫使猫奶猫灵师)

### Spellsword/魔剑士/牢剑
#### 职业介绍
你可以自称为 Spellsword（魔剑士），但你其实从未强到足以熟练挥剑。不过，谁说魔法能力不能弥补这一点呢？
#### Skills/技能
##### Primarily skill: Telekinetic Strike/主技能：念力斩
挥动你的剑，造成 55 点物理伤害。
10% 概率施加 BLEEDING（流血）状态效果。
##### Secondary skill: Piercing Strike/副技能：穿刺斩
最多蓄力 X 秒，然后释放一次中距离穿刺攻击，根据蓄力造成 85-170 点物理伤害。
最高有 50% 概率施加 BLEEDING（流血）状态效果。
>射程、伤害和流血概率会随蓄力时间提高。
>攻击速度可以缩短蓄力时间。
##### Utility skill: Quick Dash/辅助技能：迅捷冲刺
朝当前移动方向进行一次冲刺。
冷却 3 秒。
>冲刺开始时拥有极短的无敌帧。
>可以穿过 PURPLE（紫色）攻击
#### Class Upgrades/职业升级
- Spellsword: Proficiency/魔剑士：熟练
>Piercing Strike 射程 +4 米，每层 +4 米；获得 FRENZIED（狂乱）的概率 +2.5%，每层 +2.5%。
- Spellsword: Specialization/魔剑士：专精
>物理伤害 +4%（每层 +4%）。辅助技能冷却 -6%（每层 -6%）。
- Spellsword: Mastery/魔剑士：精通
>通过 BLEEDING（流血）造成伤害时恢复 2 HP，每层 +2 HP；生命回复 -100%，每层 -100%。
- Spellsword: Burst/魔剑士：爆发
>使用辅助技能后，攻击速度提高 25%，每层 +25%，持续 3 秒；辅助技能冷却速率 -20%，每层 -20%。
- Spellsword: Engagement/魔剑士：交战
>使用Quick Dash会短暂获得ENFORCED（坚壁）状态效果。辅助技能冷却 +15%（每层 +15%）
- Spellsword: Hemorrhage/魔剑士：出血
>对已经处于BLEEDING（流血）状态的敌人再次施加流血时，会把已累计的全部层数转化为HEMORRHAGE（出血）状态效果。
- Spellsword: Swift Stab/魔剑士：迅捷突刺
>你的 Piercing Strike 伤害会按超过 100% 的移动速度百分比进行加成，倍率为其中的 35%，每层 +35%。
- Spellsword: Shieldbreaker/魔剑士：破盾者
>Piercing Strike 穿透护甲并造成 25% 伤害，每层 +25%；基础攻击额外造成 25% 伤害，每层 +25%。攻击速度 -30%。
- Spellsword: Whirlwind/魔剑士：旋风
>释放完全蓄力的 Piercing Strike 会生成大型旋风，持续造成 11 点物理伤害，每层 +6；Piercing Strike 蓄力时间 +30%，每层 +30%。
#### 编者简评
说实话我没有玩过牢剑，不太清楚它的强度如何，但从技能描述来看，它的技能机制还是比较有趣的。另外，感觉上牢剑的输出还不错，但是生存能力有限，不推荐新手玩家选择。


### Twinmage/双生法师/67
#### 职业介绍
尽管你一直想成为强大的巫师，但有些人就是没有必要的天赋和先天能力。不过，你总可以依靠一对 Elemental Hands 来弥补。一次只发射一只手时，它的攻击速度会翻倍。
#### Skills/技能
>Twinmage的技能会根据你选择的Hand技能变化而变化，最多选择两种Hand技能。一个为Primary skill，另一个为Secondary skill。
##### Hand: Flaming Hand/焰之手
发射一颗火球，造成 27 点火焰伤害。
10% 概率施加 BURNING（燃烧）状态效果。
投射物速度为 16m/s，最大距离 50m。
##### Hand: Ice Hand/冰之手
发射一枚冰霜飞弹，造成 27 点冰霜伤害。
10% 概率施加 FREEZING（冰冻）状态效果。
投射物速度为 20m/s，最大距离 50m。
##### Hand: Electric Hand/电之手
施放一道闪电，造成 27 点电击伤害。
10% 概率施加 PARALYZED（麻痹）状态效果。
这是命中扫描攻击，最大距离 50m。
##### Hand: Wind Blade/风之刃
发射一道旋风，造成 27 点物理伤害。
10% 概率施加 BLEEDING（流血）状态效果。
投射物速度为 18m/s，最大距离 50m。
##### Hand: Divine Hand/圣之手
发射一颗光球，造成 35 点光耀伤害。
10% 概率施加 WEAKENED（虚弱）状态效果。
投射物速度为 24m/s，最大距离 50m。
##### Hand: Profane Hand/渎之手
发射一枚暗影飞弹，造成 27 点暗影伤害。
10% 概率施加 BREACHED（破防）状态效果。
投射物速度为 12m/s，最大距离 50m。
##### Utility skill: Quickwarp/辅助技能：瞬间移动
传送到你所指方向 15 米处。
冷却 6 秒。
#### Class Upgrades/职业升级
- Twinmage: Sinistra/双生法师：左道
>左手伤害和攻速 +5%，每层 +5%；右手伤害和攻速 -3%，每层 -3%。
- Twinmage: Dextra/双生法师：右道
>右手伤害和攻速 +5%，每层 +5%；左手伤害和攻速 -3%，每层 -3%。
- Twinmage: Specialization/双生法师：专精
>元素伤害 +7%。弹体速度 +20%。
- Twinmage: Proficiency/双生法师：熟练
>Quickwarp 距离：+5 米，每层 +5 米。
- Twinmage: Rush/双生法师：疾冲
>对敌人施加状态后获得 4 层 HASTE（疾驰），每层升级 +2。
- Twinmage: Cocktail/双生法师：鸡尾酒
>同时发射两只元素手并持续至少 4 秒后，施加状态效果的几率 +10%（每层 +10%）。
- Twinmage: Guarded/双生法师：守护
>对敌人施加状态后获得 4 层 ENFORCED（坚壁），每层升级 +2。
- Twinmage: Mastery/双生法师：精通
>你的 Elemental Hand 投射物命中后有25%的几率在 X 米半径内爆炸，每层 +X 米，造成其 75% 伤害的溅射伤害。
- Twinmage: Wicked Sign/双生法师：邪印
>Quickwarp 有 6.7% 概率给予 EMPOWERED（强化）、ENFORCED（坚壁）、HASTE（疾驰）和 FRENZIED（狂乱）各 8 层，每层升级 +2；正好 67 HP 时必定触发。
- Twinmage: Inflation/双生法师：膨胀
>Elemental Hand 弹体体积 +150%
- Twinmage: Retaliation/双生法师：反击
>受到伤害会获得 6 层「强化」状态效果（每层升级 +1 层）。冷却 6 秒。
#### 编者简评
67是一个非常有趣的职业，它的技能机制和玩法都很独特。通过选择不同的元素手技能，玩家可以根据自己的喜好和战术需求来调整输出方式。个人比较推荐的是电之手和任意一种元素手的组合，然后根据电之手的左右手加成来选择左道或右道升级。几乎所有升级均是核心升级，且还有一些通用升级需要选择。就编者个人的游玩经历，67的DPS是最高的（1500+，注：该DPS数值为极限情况下，正常情况为300-500），推荐新手玩家选择。
#### 升级选择
详见[Twinmage.png](./Twinmage.png)

### Gunmancer/枪术师/枪炮师、（光/物/火/暗/电）枪
#### 职业介绍
只要有足够的赛博强化，再加上一门脑机接口 Blast Cannon，如今谁都能成为 Sorcerer。
#### Skills/技能
>Gunmancer 的Primary skill和Secondary skill都有选项，你可以选择不同的技能来改变效果，但每种技能最多只能选择一次。
###### primary skill: VA-11 Blast Cannon/主技能：VA-11 爆能炮
每 2 秒发射一次远距离命中扫描攻击，造成 50 点电击伤害。
此外，在攻击命中的位置产生一次小爆炸，造成该投射物 50% 的伤害。
###### Primary skill: Kinetic Flechette/主技能：动能飞镖
发射一枚远距离投射物，造成 50 点物理伤害。投射物可以穿透一名敌人，然后转向最近的敌人。 15% 概率施加BLEEDING（流血）状态效果。
###### Secondary skill: Firebomb/副技能：火焰炸弹
每 X 秒发射一枚受重力影响很强的爆炸投射物，造成 50 点火焰伤害。
该攻击命中后会在较大范围内爆炸，造成投射物 100% 的伤害
###### Secondary skill: Photon Condenser/副技能：光子冷凝器
每 0.25 秒发射一枚高速子弹，造成 10 点光耀伤害。
5% 概率施加 WEAKENED（虚弱）状态效果。
###### Secondary skill: Antimatter Accelerator/副技能：反物质加速器
每 X 秒发射一次由 5 枚投射物组成的散射弹幕，每枚造成 8 点暗影伤害；按住可收窄散布。
5% 概率施加 BREACHED（破防）状态效果。
###### Utility skill: Airblast/辅助技能：气爆冲击
没有移动输入时，将自己向上弹射并短时间大幅降低重力。短暂延迟后，下一次技能会变为 CHARGED，造成 200% 伤害。
有移动输入时，朝当前方向冲刺，冷却减少 75%。是否处于移动状态只根据按键输入判断，与实际速度无关。
基础冷却 10 秒。
#### Class Upgrades/职业升级
- Gunmancer: Overcharged (VA-11 Blast Cannon)/枪术师：过载（VA-11 爆能炮）
>VA-11 Blast Cannon（VA-11 爆能炮）光束宽度 +5%，每层 +5%；电击伤害 +15%，每层 +15%。
- Gunmancer: Penetrator (Kinetic Flechette)/枪术师：穿透者（动能飞镖）
>动能飞刃命中敌人后，可以额外转向最近的敌人 1 次。
- Gunmancer: Proficiency (Firebomb)/枪术师：熟练（火焰炸弹）
>Firebomb 爆炸半径 +1m，每层 +1m；火焰伤害 +7%。
- Gunmancer: Proficiency (Photon Condenser)/枪术师：熟练（光子冷凝器）
>Photon Condenser 投射物数量 +1，每层 +1；光耀伤害 +7%。
- Gunmancer: Proficiency (Antimatter Accelerator)/枪术士：熟练（反物质加速器）
>Antimatter Accelerator 投射物数量 +1，每层 +1；暗影伤害 +5%。
- Gunmancer: Specialization/枪术师：专精
>攻击速度 +7%。辅助技能冷却 -7%
- Gunmancer: Sidestep/枪术师：侧步
>使用 Airblast Dash 后获得 2 层 HASTE（疾驰），每层升级 +1。
- Gunmancer: Bombing Run/枪术士：轰炸突袭
>使用「气爆冲刺」时会额外投出一枚炸弹，造成火焰伤害。冷却 4 秒。
- Gunmancer: Mastery/枪术士：精通
>CHARGED 射击伤害 +25%（每层 +25%）。
- Gunmancer: Marksman (VA-11 Blast Cannon)/枪术士：神射手（VA-11 爆能炮）
>周期性抛出硬币。用 Blast Cannon 击中硬币会把爆炸导向最近敌人，并使爆炸伤害提高 500%，每层 +24%；硬币尺寸 +10%，每层 +10%。由于只乘算爆炸部分，实际总伤害约为普通射击的 1.66 倍。
- Gunmancer: Lucky Seven/枪术士：幸运七
>主技能的每第 7 发子弹伤害 +50%。主技能的每第 4 发子弹伤害 -50%。
#### 编者简评
枪术师在v0.6更新后迎来了一波小加强，尤其是物枪（Kinetic Flechette）得到了显著增强，添加了转向机制，使其在群体战斗中表现更为出色，且Gilgamesh的二阶段受击判定区域非常小，而且很多动~~（多动症之神）~~，物枪的追踪可以很好的克制，若升级选的不错的话实测也能有上千DPS的输出（注：该DPS数值为极限情况下，正常情况为500-650）。推荐新手玩家选择。
#### 升级选择
详见[Gunmancer (Kinetic Flechette).png](./Gunmancer%20(Kinetic%20Flechette).png)、[Gunmancer (VA-11 Blast Cannon, outdated).png](./Gunmancer%20(VA-11%20Blast%20Cannon,%20outdated).png)
**<br>编者没玩过新版本的VA-11 Blast Cannon，图示的升级为v0.5版本时使用</br>**

### Fistmage/拳法师/拳师、牢拳
#### 职业介绍
像你这样满脑子肌肉的人本来没有理由成为巫师，但你还是坚持了下来，并且不知怎么就把它做成了。强力的坦克/伤害混合职业，特别重视反击。
#### Skills/技能
##### Primary skill: Aura Fist/主技能：气劲拳
最多蓄力 1 秒后释放拳击，根据蓄力程度造成 55-100 点物理伤害。
##### Secondary skill: Deflecting Swipe/副技能：拨挡挥击
挥击，造成 40 点物理伤害。
挥击后会获得一个短暂的判定窗口，期间下一次受到的伤害将被完全偏转。成功偏转一次攻击会给予你 12 层「强化」与「坚壁」，治疗 10 点生命，并立即重置冷却。
如果这次「拨挡挥击」判定为完美格挡（Perfect Parry），则改为治疗 30 点生命。
冷却 5 秒。
##### Utility skill: Super Endurance/辅助技能：超耐力
净化所有负面状态效果5秒，进入持久姿态。在此期间，你会失去75%的移动速度，减少X%的伤害，提升400%的击退抗性，并获得更高的仇恨吸引。
以上所有属性都是基础属性的乘数，超过任何上限。
12秒冷却。
#### Class Upgrades/职业升级
- Fistmage: Proficiency/拳法师：熟练
>成功使用 Deflecting Swipe 时，治疗 5 HP，每层 +5 HP，并在自身周围召唤一个光环，为附近队友治疗，治疗量为你个人治疗量的一半。
- Fistmage: Specialization/拳法师：专精
>物理伤害 +4%（每层 +4%）。击退抗性 +7%（每层 +7%）。
- Fistmage: Mach Punch/拳法师：音速拳
>根据当前移动速度，获得相当于25%（每层+25%）的额外物理伤害。7秒冷却。这不会影响持续伤害，只能由你的主技能触发。
- Fistmage: Mastery/拳法师：精通
>成功偏转时，获得的 EMPOWERED（强化）和 ENFORCED（坚壁）层数 +1，每层升级再 +1。完美招架时，获得7层ADRENALINE（肾上腺素）状态效果。Deflecting Swipe 冷却 -7%（每层-7%）
- Fistmage: Blast Radius/拳法师：爆炸半径
>释放满蓄力的Aura Fist 会在你周围引发爆炸，造成火焰伤害并有 10% 概率施加BURNT（燃烧）状态效果；爆炸会击退敌人。攻击速度 -30%
- Fistmage: Rage/拳法师：狂怒
>成功使用 Deflecting Swipe 偏转攻击后，攻击速度翻倍并持续 4 秒，同时获得 3 层HASTE（疾驰）状态效果（每层升级 +1 层）。该效果最多只能叠到 10 层HASTE（疾驰）。偏转失败则会短暂获得BREACHED（破防）状态效果.
- Fistmage: Runner/拳法师：疾行者
>在充能Aura Fist 时，移动速度会在10秒内（每级减2秒）逐渐翻倍。可超过移动速度上限。
- Fistmage: Apply Force/拳法师：施力
>成功偏转后会获得 1 层APPLY FORCE（蓄力）状态效果。在该状态生效时释放满蓄力的Aura Fist，会发射一枚远程投射物造成 50 点物理伤害，并消耗 1 层该状态效果。Deflecting Swipe 冷却 +30%（每层 +30%）
- Fistmage: Extreme Regimen/拳法师：极限训练
>使用 Super Endurance 时获得GREATER RESILIENCE（高等韧性）状态效果：可以格挡一次普通伤害，并把一次紫色攻击的伤害减半。
#### 编者简评
编者有幸玩过几次牢拳，说实话，不会利用偏转机制的玩家很难玩好这个职业，我玩起来很牢。牢拳的技能机制非常独特，尤其是偏转技能，如果能熟练掌握，可以在战斗中获得极大的优势。推荐有一定游戏经验的玩家尝试。

### Spellhammer/咒锤战士/（砸/丢）锤
#### 职业介绍
你拥有很高的魔法资质，却决定成为狂野的野蛮人。会被你砸碎的恐怕不只是惯例和常识。
#### Skills/技能
>Spellhammer 的Secondary skill有选项，你可以选择不同的技能来改变效果，但只能选择一个。
##### Primary skill: Pummel/主技能: 连环重锤
挥动你的锤子，造成 90 点物理伤害并击退敌人。
挥动期间你的移动速度会提高到两倍，并且该技能会直接随移动速度缩放。
##### Secondary skill: Jump Smash/副技能: 跃击重砸
向上跳起，然后释放技能砸回地面，造成 130 点物理伤害并击退敌人。落在敌人正上方时，会根据初始高度追加伤害，并把你再次弹起。
##### Secondary skill: Chuck/副技能: 掷锤
按住后松开，将锤子投出。伤害随蓄力时间提升，造成 65-130 点物理伤害。弹体速度为 40 单位。
##### Utility skill: Disperse/辅助技能: 散势
释放一次大范围爆炸，造成 130 点物理伤害，并向后跳开。
冷却 8 秒。人在空中时仍会恢复冷却，但速度明显更慢。
#### Class Upgrades/职业升级
- Spellhammer: Proficiency (Jump Smash)/咒锤战士：熟练（跃击重砸）
>击退力 +10%，每层 +10%；Jump Smash 强度 +5%，每层 +5%。
- Spellhammer: Proficiency (Chuck)/咒锤战士：熟练（掷锤）
>击退力 +10%，每层 +10%；投出锤子的重力下降 -10%，每层 -10%。
- Spellhammer: Specialization/咒锤战士：专精
>移动速度 +7%。跳跃高度 +12%。
- Spellhammer: Boosted/咒锤战士：强化
>Disperse 爆炸强度 +10%；Disperse 爆炸伤害 +10%。
- Spellhammer: Mastery (Jump Smash)/咒锤战士：精通（跃击重砸）
>在敌人正上方施放 Jump Smash 会使冷却减少 15%，每层 -15%。
- Spellhammer: Mastery (Chuck)/咒锤战士：精通（掷锤）
>命中后，你投出的锤子会朝最近的敌人弹跳 1 次，每层 +1 次。投出锤子的重力下降 -5%，每层 -5%。
- Spellhammer: Sus-tain (Jump Smash)/咒锤战士：持续（跃击重砸）
>对敌人使用跃击重砸会给予你 4 层REJUVENATION（复苏）状态效果（每层 +1 层）。暴击伤害 -15%。
- Spellhammer: Sus-tain (Chuck)/咒锤战士：持续（掷锤）
>掷出的锤子命中敌人会给予你 4 层REJUVENATION（复苏）状态效果（每层 +1 层）。暴击伤害 -15%。
- Spellhammer: Concussion (Jump Smash)/咒锤战士：震荡（跃击重砸）
>施放高威力 Jump Smash 会造成额外电击伤害，并有 50% 概率施加 PARALYZED（麻痹）状态效果。
- Spellhammer: Concussion (Chuck)/咒锤战士：震荡（掷锤）
>成功命中时生成范围效果，造成电击伤害，并有 50% 概率施加 PARALYZED（麻痹）。
- Spellhammer: Helldive (Jump Smash)/咒锤战士：地狱俯冲（跃击重砸）
>蓄力跃击重砸的伤害 +20%。跳跃高度 -35%。暴击率 -5%。
- Spellhammer: Helldive (Chuck)/咒锤战士：地狱俯冲（掷锤）
>满蓄力掷锤的伤害 +15%。弹体速度 -50%。暴击率 -5%。
- Spellhammer: Juggernaut (Jump Smash)/咒锤战士：主宰（跃击重砸）
>施放高威力 Jump Smash 会给予你短暂的 ENFORCED（坚壁）状态效果。
- Spellhammer: Juggernaut (Chuck)/咒锤战士：主宰（掷锤）
>满蓄力投掷会给予短暂的 EMPOWERED（强化）。最多持有 5 层；每层该升级使上限 +2。
#### 编者简评
编者体验过它的两种玩法，砸锤更适合有一定游戏经验的玩家，丢锤则更适合新手玩家。但它们的共同点是难以应对移动靶，在多动症多如狗的当前版本显得略有劣势，但锤的单次伤害是很可观的（可能有1000+）。
#### 升级选择
详见[Spellhammer (Chuck).png](./Spellhammer%20(Chuck).png)
<br>暂无Jump Smash的升级推荐（因为编者不会玩）</br>

### Shield Mage/盾法师/牢盾
#### 职业介绍
你是一种一直太怕受伤的巫师。俗话说，有时候最好的进攻就是防守。大概是这样。
#### Skills/技能
##### Primary skill: Offensive Strike/主技能：攻势打击
向前投掷你的盾牌，造成 75 点物理伤害。使用 Defensive Stance 时，向前盾击，造成 50 点物理伤害并击退敌人。
##### Secondary skill: Defensive Stance/副技能：防御姿态
按住以用盾牌防御，格挡命中盾牌的来袭伤害，并使你的移动速度降低 X%。
格挡攻击时会为 ICEBURST 充能。放下盾牌时释放 ICEBURST，在你周围半径内（最高50单位）造成高额冰霜伤害（最高500点）；伤害与你承受的伤害成比例，威力与格挡的攻击数量成比例。
##### Utility skill: Evasive Maneuver/辅助技能：闪避机动
在原地停住 5 秒，在你周围生成不可穿透的护盾。该护盾会使 PURPLE（紫色）攻击伤害降低 50%，并提高你的仇恨。使用 Defensive Stance 时，则朝移动方向进行一次短冲刺。
#### Class Upgrades/职业升级
- Shield Mage: Proficiency/盾法师：熟练
>提高 Defensive Stance 护盾的作用范围 X%，每层 X%。
- Shield Mage: Specialization/盾法师：专精
>防御 +2%（每层 +2%）。辅助技能冷却 -8%（每层 -8%）
- Shieldmage: Unbreakable/盾法师：不屈
>来自 Purple Attacks 的伤害 -5%；Evasive Maneuver 护盾激活时，来自 Purple Attacks 的伤害 -10%。
- Shieldmage: Bulldozer/盾法师：推土机
>使用 Evasive Maneuver 冲刺时，会在冲刺方向造成冰霜伤害并击退敌人。
- Shieldmage: Ice Burst/盾法师：冰霜爆发
>每格挡一次攻击，提高 Ice Burst 的充能威力。
- Shieldmage: Mastery/盾法师：精通
>提高 Evasive Maneuver 护盾尺寸 X%，每层 X%。
- Shieldmage: Drainshield/盾法师：吸盾
>在防御姿态下格挡伤害时回复 5 点生命（每层 +3 点）。生命回复 -100%（每层 -100%）。
- Shieldmage: Rally Up/盾法师：鼓舞
>使用 Evasive Maneuver 护盾会给予你和附近盟友短暂的 EMPOWERED（强化）状态效果。
- Shieldmage: Warden/盾法师：守护者
>使用 Evasive Maneuver 护盾会让自身与所有队友获得RESILIENCE（韧性）状态效果，可以格挡一次伤害。辅助技能冷却 +50%（每层 +50%）
#### 编者简评
编者没有玩过牢盾，无法给出很公正的评价，但盾对一个队伍的重要性是不言而喻的，而且上手简单，除了输出能力不高以外，没什么缺点。

### Thaumaturge/奇迹师/书奶
#### 职业介绍
人生中，带来愉悦的一切也都会带来痛苦，用来衡量那份愉悦。伤害敌人会积累 LIFE ENERGY。
#### Skills/技能
##### Passive/被动效果
伤害敌人会积累 LIFE ENERGY；获得的 LIFE ENERGY 与你造成的伤害成比例。
##### Primary skill: Foul Pustule/秽脓
射出一团毒液球，造成 25 点毒伤害。
10% 概率施加 8 层 POISONED（中毒）状态效果。
投射物速度为 Xm/s，最大距离 Xm。
##### Secondary skill: Pain Exchange/痛楚转移
花费 25% LIFE ENERGY，为自己或一名盟友恢复 60 HP。
冷却 3 秒。治疗自己时，冷却时间增加 75%。
Thaumaturge（奇迹师）初始受到治疗只有 50%，因此对自己使用时基础治疗量减半。
##### Utility skill: Soulborne/魂附
进入吸收姿态 4 秒，提高移动速度 X%，提高防御 X%，并把受到的任何伤害转化为 LIFE ENERGY。
以上所有属性都是基础属性的乘数，超过任何上限。
冷却 10 秒。
#### Class Upgrades/职业升级
- Thaumaturge: Keen Eye/奇迹师：锐眼
>Pain Exchange 范围 +15 米，每层 +15 米。
- Thaumaturge: Proficiency/奇迹师：熟练
>Pain Exchange 治疗量 +5，每层 +5；冷却 -10%，每层 -10%。
- Thaumaturge: Specialization/奇迹师：专精
>毒素伤害 +6%（每层 +6%）。受到的治疗 +4%（每层 +4%）
- Thaumaturge: Mastery/奇迹师：精通
>施放 Pain Exchange 所需 LIFE ENERGY -3%，每层 -3%。
- Thaumaturge: Moribound/奇迹师：濒死
>受到状态效果伤害时回复 1 点生命（每层 +1 点）。受到的治疗 -10%（每层 -10%）
- Thaumaturge: Schadenfreude/奇迹师：幸灾乐祸
>施加POISONED（中毒）状态效果时会给予你一个短暂的HASTE（急速）状态效果（每层 +3 层，最多 6 层）。
- Thaumaturge: Splitshot/奇迹师：分裂射击
>使用 Foul Pustule 时额外发射一个投射物；投射物散布 +2.5%，每层 +2.5%；伤害 -40%，每层 -40%。
- Thaumaturge: Doping/奇迹师：兴奋剂
>Pain Exchange 目标获得 6 层 ENFORCED（坚壁），每层升级 +4。对自己使用时最多施加 3 层，无法突破；对他人使用时上限为 X 层。Pain Exchange冷却 +15%
- Thaumaturge: Everlife/奇迹师：永生
>花费 100% LIFE ENERGY 复活带有 MORTAL CURSE（致命诅咒）的玩家。使用后自身获得 40 层 BREACHED（破防）和 WEAKENED（虚弱），每层升级 -20 层；本回合最大生命 -25；LIFE ENERGY 获取 -10%，每层 -10%。
- Thaumaturge: Splashback/奇迹师：溅射
>治疗自己或盟友时，在目标处产生半径 3 米（每层 +3 米）的爆炸，造成 75 点（每层 +25）毒素伤害。
#### 编者简评
书奶说实话从最高游戏推出开始就比较牢，而且很吃升级，几乎是固定的模式，没有一定游戏理解很难玩好书奶，但书奶又是这个游戏至关重要的一个职业，一个10人的队伍推荐要有2名书奶和一名[猫奶](#nekomancer死灵猫使猫奶)，才能很好的应对最终boss之一Gilgamesh，不推荐新手玩家游玩。
#### 升级选择
详见[Thaumaturge.png](./Thaumaturge.png)
<br>另，Thaumaturge: Everlife/奇迹师：永生也是值得选取的升级，但图示的那一局我没遇到</br>

### Nekomancer/死灵猫使/猫奶、猫灵师
#### 职业介绍
就算你的骨骸已经重生为魔法巫妖死灵术士，也不代表你不能继续保留爱好和个性。收集会周期性出现在场地上的 SOUL（灵魂）。被击杀的敌人有概率留下 SOUL。
#### Skills/技能
##### Passive/被动效果
收集每 40 秒在场地周围生成的 SOUL（灵魂）。被击杀的敌人有 X% 概率留下 SOUL。
##### Primary skill: Staff of Feline Mortality/主技能：猫科殒命之杖
发射一枚投射物，造成 20 点暗影伤害。命中的敌人会被标记为 Undead Kitties（亡灵猫）的目标。
10% 概率施加 BREACHED（破防）状态效果。
##### Secondary skill: Call of the Undead/副技能：亡者召唤
花费 1 个 SOUL（灵魂），召唤多种 Undead Kitties（亡灵猫）之一。
使用技能会开始召唤流程。在召唤流程期间再次按下技能，可以在召唤物之间切换选择。
Undead Kitties（亡灵猫）不会直接继承升级，但会获得玩家由升级得到的等量属性，包括元素伤害、总伤害、攻击速度、投射物速度、投射物距离、暴击率、暴击伤害和状态效果概率。
最大召唤数量随玩家数量缩放：
你最多可以持有 5 个 SOUL（灵魂），未收集的 SOUL 会在 30 秒后消失。
>Undead kitties有：每次攻击造成25暗影伤害的Zombie Kitty、每次攻击造成35物理伤害的Ballista Kitty、每次攻击造成36火属性伤害的Balloon Kitty、回复附近玩家血量的Totem Kitty。
><br>Undead kitties造成的伤害比猫奶自身高；Totem Kitty无法移动，其他的猫均可移动，但速度较慢</br>
##### Utility skill: Spirit Drift/灵魂漂移
进入无敌（**无法抵挡Purple Attacks**）并向前漂移，持续 2 秒。
冷却 10 秒。
#### Class Upgrades/职业升级
- Nekomancer: Proficiency/死灵猫使：熟练
>被击杀敌人留下 Soul（灵魂）的概率 +15%；随机 Soul 生成速率 +50%。
- Nekomancer: Specialization/死灵猫使：专精
>元素伤害 +7%。辅助技能冷却 -5%
- Nekomancer: Bloated/死灵猫使：臃肿
>猫咪会继承你 20% 的总防御与元素防御。总防御 +3%
- Nekomancer: Death Blossom/死灵猫使：死亡绽放
>Kitty Totem（猫图腾）治疗速度 +10%；Kitty Totem 治疗范围 +1m；伤害 -3%。任何在猫图腾范围内的玩家都会获得一个短暂的REJUVENATION（复苏）状态效果。
- Nekomancer: Mastery/死灵猫使：精通
>每持有 1 个灵魂，获得：总伤害 +6%（每层 +6%）生命回复 +40%（每层 +40%）
- Nekomancer: Soul Detonation/死灵猫使：灵魂引爆
>小猫死亡时产生半径 2 米（每层 +1.5 米）的暗影爆炸，并有 50% 概率施加 BREACHED（破防）。
- Nekomancer: Necropact/死灵猫使：死灵契约
>当至少有 1 只召唤小猫存在时：你在低 HP 时受到的任何伤害，其 600% 会被转移给 1 只小猫。
- Nekomancer: Soul Vortex/死灵猫使：灵魂漩涡
>200 米内且在你视线范围内的灵魂会被拉向你。
#### 编者简评
猫奶，最悠闲（存疑）的职业，毕竟输出和治疗都可以丢给可爱的猫猫们，你只需要到处逛街，收集Soul就好了，不过丢好Totem Kitty也是一门学问呢。
#### 升级选择
详见[Nekomancer (outdated).png](./Nekomancer%20(outdated).png)
**<br>此为v0.5版本的升级选择，编者没有在v0.6版本玩完一整局猫奶</br>**

## Upgrades/通用升级
### Vendors/商人
- [Crystal of Perseverance/坚忍之晶](#crystal-of-perseverance坚忍之晶)
- [Amaterasu/天照](#amaterasu天照)
- [Chrono Wizard/时序巫师](#chrono-wizard时序巫师)

#### Crystal of Perseverance/坚忍之晶
>提供与最大生命值、防御以及一切生存能力相关的升级。
- Big Belly
>击退抗性 +15%（每层 +15%）。最大生命 +5（每层 +5）
- Fluffy
>最大 HP：+10（每层 +10）
- Gluttonous
>受到治疗 +7%（每层 +7%）
- Swarm Enforcer
>你周围 32 米内每有一个敌人，获得 +1.5% 防御。（每层 +1.5% 防御）
- Vitality
>生命回复：+80%（每层 +80%）
- Vital Drain
>暴击回复 2 HP（每层 +2 HP）
- Adrenaline Fiend
>使用辅助技能回复 6 HP（每层 +6）；辅助技能冷却速率 +7%（每层 +7%）；受到治疗 -15%（每层 -15%）
- Big and Lazy
>静止至少 1 秒时，获得额外 200% 生命回复（每层 +100%）；移动时生命回复设为 0%。
- Big and Round
>击退抗性 +50%（每层 +50%）；最大 HP +30（每层 +30）；跳跃高度 -10%（每层 -10%）；移动速度 -10%（每层 -10%）
- Cold Blooded
>受到的 FROZEN（冰冻）层数减少 X（每层升级再减 X）；冰霜防御 +15%（每层 +15%）；火焰防御 -15%（每层 -15%）
- Conductive Armor
>物理防御 +20%（每层 +20%）；受到的 BLEEDING（流血）层数减少 X（每层再减 X）；元素防御 -5%（每层 -5%）
- Elemental Armor
>元素防御 +10%（每层 +10%）。物理防御 -7%（每层 -7%）。
- Green Thumb
>受到的治疗 +15%。生命回复 -80%
- Holy Blessing
>生命降至 LOW HP 时会引发一次大爆炸，造成 260 点光耀伤害（每层升级 +260），并 100% 施加 X 层「虚弱」状态效果。光耀防御：+15%（每层 +15%）暗影防御：+15%（每层 +15%）总伤害：-5%（每层 -5%）
- Inner Cleanse
>小幅提高对一切负面状态效果的抗性。
- Iron Skin
>防御：+15%（每层 +15%）最大生命 -15（每层 -15）
- Last Stand
>受到伤害后若剩余 1-5 HP（每层+1），获得 3 层 INVINCIBLE（无敌），每层+2。冷却30s
- Life Leech
>造成伤害时回复 1 HP（每层 +1）；总伤害 -10%、生命回复 -50%、受到治疗 -20%（均按层叠加）
- Masochist
>受到的 PARALYZED（麻痹）层数减少 X（每层再减 X）；电击防御 +15%（每层 +15%）；物理防御 -10%（之后每层 -15%）
- Nature's Gift
>每 10 秒在 stage（阶段）的随机位置生成最多 3 个个人 Healing Aura（每级 +1），每个会为你治疗 20。
- Sacrificial Lamb
>死亡时，为其他每位队友治疗 15 HP（每层 +15 HP），并为其施加X层REJUVENATION（复苏）状态效果（每层 +X层）。
- Benison of Purification
>周期性向 64 米内最近敌人发射 25 点光耀伤害投射物（每层 +X）；暗影防御 +10%、总防御 -5%（均按层叠加）
- Big and Wrathful
>LOW HP 时造成伤害 +20%；LOW HP 阈值提高 20%；LOW HP 时防御 -25%
- Curse of Wrath
>周期性向 32 米内最近敌人发射 25 点暗影伤害投射物（每层 +X）；光耀防御 -20%（每层 -20%）
- Glass Cannon
>伤害 +25%（每层 +25%）；生命 -60（每层 -60）
- Healthy Guard
>保持 FULL HP 15 秒后（每层 -X 秒），下一次受到的伤害减少 50%（每层 +50%）
- Mass Aspect
>生命：+75（每层 +75）；移动速度：-30%（每层 -30%）
- Volatile Tenacity
>高于 LOW HP 时受到致命伤害会保留 1 HP；冷却 150 秒，每层使冷却恢复速率 +25%

#### Amaterasu/天照
>提供与移动速度、攻击速度以及技能冷却相关的升级。
- Athletic
>移动速度：+10%（每层 +10%）
- Eagle Eye
>投射物速度 +35%（每层 +35%）
- Hawkeye
>投射物距离 +10 米（每层 +10 米）；投射物散布 -1%（每层 -1%）
- Panic Sense
>每有一名 32 米内的敌人，就获得 +4% 移动速度（每层 +4%）。
- Quick Breath
>辅助技能冷却速率 +10%（每层 +10%）
- Springfoot
>跳跃高度：+20%（每层 +20%）
- Swift Hands
>攻击速度：+15%（每层 +15%）
- Leg Day
>受到的 HEAVY 层数减少 X（每层再减 X）；移动速度 +5%、跳跃高度 +10%（均按层叠加）
- Reactive Panic
>受到伤害会获得 5 层FRENZIED（狂乱）状态效果（每层升级 +3 层）。
- Smell the Roses
>进入 LOW HP 时获得 5 层 HASTE（疾驰），每层升级 +2；冷却 30 秒
- Sniper Vision
>弹体射程 +25 米（每层 +25 米）。弹体散布 -2%（每层 -2%）。弹体速度 -45%（每层 -45%）
- Thunder Aura
>每秒对周围敌人造成 25 点电击伤害（每层 +5）；总伤害 -10%（每层 -X%）；移动速度 -5%（每层 -X%）
- Berserker's Soul (Melee)
>用主技能造成伤害会获得一层「狂战士之魂」，最多 90 层。每层提供 +0.64%（每层升级 +0.64%）总伤害、+1.28%（每层升级 +1.28%）攻击速度，以及 -X% 生命回复。受到伤害会清空全部层数。总伤害：-20%（每层升级 -20%）攻击速度：-40%（每层升级 -40%） * 满层时净收益为：总伤害 +45%、攻击速度 +90%、生命回复 -50%。
- Berserker's Soul (Ranged)
>用主技能造成伤害会获得一层「狂战士之魂」，最多 90 层。每层提供 +0.32%（每层升级 +0.32%）总伤害、+0.64%（每层升级 +0.64%）攻击速度，以及 +X% 投射物散布。受到伤害会清空全部层数。总伤害：-10%（每层升级 -10%）攻击速度：-20%（每层升级 -20%） * 满层时净收益为：总伤害 +22.5%、攻击速度 +45%、投射物散布 +2%。
- Big and Speedy
>辅助技能冷却速率 +50%（每层 +50%）；总防御 -20%（每层 -20%）
- Featherweight
>移动速度 +30%（每层 +30%）；总防御 -10%（每层 -10%）
- Heavy Hand
>伤害 +20%（每层 +20%）；攻击速度 -40%（每层 -40%）
- Partial Flight
>额外跳跃：+1（每层 +1）
- Rapid Fire
>攻击速度：+50%（每层 +50%）；总伤害：-10%（每层 -10%）
- Spray and Pray
>弹体速度 +125%（每层 +125%）。弹体射程 -25 米（每层 -25 米）。弹体散布 +2%（每层 +2%）
- Way of the Law
>周期性在 STOP 与 GO 之间切换。STOP 降低移动与攻速但提高伤害；GO 提高移动与攻速但降低伤害

#### Chrono Wizard/时序巫师
>提供与暴击、伤害、状态效果以及高风险高回报相关的升级。职业升级也在此处获取。
- Full Focus
>暴击率 +5%；暴击伤害 +5%
- Potent Strike
>暴击有额外 3% 几率施加状态效果。
- Sorcerer's Mastery
>ELEMENTAL（元素）伤害 +7%
- Strength
>物理伤害 +7%（每层 +7%）
- An IQ Too High?
>元素伤害 +20%、投射物速度 -15%、攻击速度 -5%（均按层叠加）
- Clutch or Kick
>队伍中每有一名死亡玩家，获得 +5% 伤害（每层 +1%）
- Cutting Edge
>施加 BLEEDING（流血）状态效果的几率 +10%；PHYSICAL（物理）防御 -5%
- Electric Aspect
>电击防御 +15%（每层 +15%）。电击伤害 +15%（每层 +15%）。施加PARALYZED（麻痹）状态效果的几率 +5%（每层 +5%）。物理防御 -10%（每层 -10%）。
- Fire Aspect
>FIRE（火焰）防御 +15%；FIRE 伤害 +15%；施加 BURNING（燃烧）状态效果的几率 +5%；FROST（冰霜）防御 -10%
- Frost Aspect
>FROST（冰霜）防御 +15%；FROST 伤害 +15%；施加 FROZEN（冰冻）状态效果的几率 +5%；FIRE（火焰）防御 -10%
- Greater Focus
>暴击率 +10%（每层 +10%）。暴击伤害 +15%（每层 +15%）。防御 -5%（每层 -5%）
- Luminous Aspect
>LUMINOUS（光耀）伤害 +15%；SHADOW（暗影）防御 +15%；施加 WEAKENED（虚弱）状态效果的几率 +5%；ELEMENTAL（元素）防御 -5%
- Monkey Power
>物理伤害 +17%（每层 +17%）。元素伤害 -5%（每层 -5%）。攻击速度 -10%（每层 -10%）。
- Poison Aspect
>毒素伤害 +15%（每层 +15%）。毒素防御 +15%（每层 +15%）。施加POISONED（中毒）状态效果的几率 +10%（每层 +10%）。受到的治疗 -8%（每层 -8%）
- Shadow Aspect
>SHADOW（暗影）伤害 +15%；施加 BREACHED（破防）状态效果的几率 +5%；LUMINOUS（光耀）防御 -10%
- Sticky
>对敌人施加状态时额外施加 2 层（每层升级 +2）；自身受到负面状态时额外增加 X 层（每层升级 +X）
- Charged Strike
>暴击产生物理爆炸，造成 25 伤害（每层 +10）；暴击率 -5%（每层 -5%）
- Flaming Spirit
>FULL HP 时使用主技能会发射造成 16 点火焰伤害的火球（每层 +8）；受到治疗 -5%、生命回复 -20%（均按层叠加）
- Frozen Heart
>FULL HP 时使用主技能会发射造成 18 点冰霜伤害的冰锥（每层 +9）；受到治疗 -5%、生命回复 -20%（均按层叠加）
- Pocket Abacus
>你造成的每第 5 次（每层-1）伤害会变为必定暴击；暴击伤害 +10%；非暴击伤害 -5%；你不会再有暴击率（你只能通过这种方式暴击）
- Third Law
>受伤时，把原始伤害的 150%（每层 +25%）作为物理伤害返还给周围敌人；Fistmage（拳法师）偏转时返还 50%
- Warrior's Will
>使用辅助技能会获得 5 层EMPOWERED（强化）状态效果（每层升级 +1 层）。辅助技能冷却速率 -15%（每层 -15%）

## 状态效果
- Adrenaline/肾上腺素
>使伤害、移动速度、防御等属性 +30%。获取条件：在 5 人以上的实例中成为最后一名存活者。
- Empowered/强化
>玩家造成的所有伤害 +25%；敌人造成的所有伤害 +50%。每层持续 1.05 秒。
- Enforced/坚壁
>玩家与敌人受到的所有伤害减半；不降低 PURPLE（紫色）攻击伤害。每层持续 1.1 秒。
- Frenzied/狂乱
>攻击速度 +50%。每层持续 1.5 秒。
- Haste/疾驰
>移动速度 +50%。每层持续 1.15 秒。
- Invincible/无敌
>完全免疫伤害。每层持续 1 秒。
- Rejuvenation/复苏
>生命回复效果提升 200%，受到的治疗效果提升 50%。
- Resilience/韧性
>抵挡下一次伤害后移除全部层数；无法抵挡 PURPLE（紫色）攻击。每层持续 10 秒。
- Greater Resilience/高等韧性
>格挡一次伤害，随后移除全部层数。层数持续 10 秒。 *对紫色攻击有效：使受到的伤害降低 50%。
- Breached/破防
>玩家受到的所有伤害 +75%；敌人受到的所有伤害 +25%。每层持续 0.7 秒。
- Decayed/衰朽
>受到治疗降为 0%。每层持续时间未知。玩家无法施加。
- Frozen/冰冻
>每层到期时造成冰霜伤害，每层持续 0.6 秒。每层都有概率施加“结冰”：移动速度 -75%；玩家的辅助技能冷却速率 -90%。
- Heavy/沉重
>跳跃高度降为 0%。每层持续时间未知。玩家无法施加。
- Paralyzed/麻痹
>每层到期时造成雷电伤害，每层持续 0.3 秒。每层都有概率施加“僵直”：移动速度 -99%，并且无法攻击。不会打断正在播放攻击动画的敌人或 Boss。
- Sticky/黏着
>玩家移动速度与跳跃高度降至 25%。每层持续时间未知。玩家无法施加。
- Weakened/虚弱
>玩家造成的所有伤害 -75%；敌人造成的所有伤害 -25%。每层持续 0.8 秒。
- Bleeding/流血
>一层到期时造成物理伤害；每层持续 0.8 秒.
- Burning/燃烧
>一层到期时造成火焰伤害；每层持续 0.5 秒。
- Hemorrhaged/出血
>层数到期时造成物理伤害，伤害量为「流血」的 2 倍。层数持续 0.8 秒。
- Poisoned/中毒
>一层到期时造成毒素伤害；每层持续 0.75 秒。
- Apply Force/蓄力
>可供 Fistmage: Apply Force（拳法师：施力）消耗。
- Collapse/崩坏
>每 0.1 秒造成相当于自身生命 10% 的伤害；Boss 战超过时间限制后会不断重新施加。
- Dead/倒地
>无法行动，但仍可被复活；首次复活后获得 Mortal Curse（致命诅咒）。
- Mortal Curse/致命诅咒
>再次死亡后无法正常复活；Thaumaturge: Everlife（奇迹师：永生）可以绕过。
- Revive Protection/复活保护
>复活后获得 2～5 秒伤害保护。
- Stop and Go/行与停
>在 STOP 与 GO 之间切换，详见 Way of the Law（律法之道）。
- Vital/生机
>表示 Healthy Guard（健者守护）已经生效。
- Volatile/易爆
>只要受到致命伤害前不处于 LOW HP，就能承受该次伤害并保留 1 HP。

## 符文与符文诅咒
### 符文
#### 简介
>符文是可以带进本局的强力强化。你需要先完整通关一次，才会随机解锁一个符文。装备地点是开局大厅的 Workshop Anvil（工坊铁砧）。
><br>共有四个符文槽位，但第一个符文要到 Penumbral（半影）阶段才会激活，之后每个槽位的激活阶段依次提高，直到 Eclipse（全蚀）。</br>
>截至 Patreon Playtest Demo，只能使用 Penumbral（半影）与 Antumbral（伪本影）两个符文槽位。
><br>符文虽然强力，但每个槽位激活时都会附带一个随机的强化符文诅咒；诅咒可以重复抽到同一个。Penumbral 槽给 1 层诅咒，Antumbral 槽给 2 层，依此类推。</br>
#### 符文列表
- Focus Growth
>暴击率 +10%（+10%/阶段）
- Cleansing Growth
>提高对一切负面状态效果的抗性（每个阶段抗性进一步提升）
- Recovery Growth
>辅助技能冷却 -20%（-20%/阶段）
><br>可防止符文诅咒：哮喘</br>
- Power Growth
>伤害 +10%（+10%/阶段）
><br>可防止符文诅咒：空洞</br>
- Dexterity Growth
>攻击速度 +30%（+30%/阶段）
><br>可防止符文诅咒：萎缩</br>
- Precision Growth
>暴击伤害 +25%（+25%/阶段）
- Health Growth
>最大生命 +25（+25/阶段）
><br>可防止符文诅咒：汲取</br>
- Satiety Growth
>受到的治疗 +20%（+20%/阶段）
><br>可防止符文诅咒：缺氧</br>
- Defense Growth
>防御 +10%（+10%/阶段）
><br>可防止符文诅咒：脱落</br>
- Rejuvenating Growth
>生命回复 +200%（+200%/阶段）
><br>可防止符文诅咒：贫血</br>
- Skybound
>额外跳跃 +1（+1/阶段），跳跃高度 +25%（+25%/阶段）
><br>可防止符文诅咒：怠惰</br>
- Way of the Turtle
>最大生命 +40（+40/阶段），防御 +15%（+15%/阶段），移动速度 -20%（-20%/阶段）
><br>可防止符文诅咒：汲取</br>
- Active Guard
>使用辅助技能时有 5% 几率获得RESILIENCE（韧性）状态效果（+2%/阶段）
><br>可防止符文诅咒：紫罗兰</br>
- Manic Gambit
>任何被献祭的神器都会给予其属性 300% 的加成（+100%/阶段），每个阶段只能获得 1 枚代币
- Big and Greedy
>找到额外代币的几率 +20%（+15%/阶段）。成功时还有 50% 几率再获得一枚额外代币。激活时所获得的诅咒层数 +1
- Big and Needy
>购买普通升级后返还代币的几率 +17%（+4%/阶段）。激活时所获得的诅咒层数 +1
- Big and Picky
>选择升级时多 1 个选项。选择升级时多 1 次重掷（+1 次/阶段）.激活时所获得的诅咒层数 +1
- Big and Insured
>获得 1 枚代币（伪本影及以后阶段再 +1）。选择升级时多 1 次重掷（+1 次/阶段）
- Precise Shot
>弹体速度 +35%（+35%/阶段）。弹体射程 +10 米（+10 米/阶段）。弹体散布 -2%（-2%/阶段）
><br>可防止符文诅咒：震颤</br>
- Stalwart Will
>防御 +20%（+20%/阶段）。伤害 -10%（-10%/阶段）
><br>可防止符文诅咒：脱落</br>
- Way of the Rabbit
>跳跃高度 +30%（+30%/阶段）。移动速度 +15%（+15%/阶段）.防御 -10%（-10%/阶段）。
><br>可防止符文诅咒：怠惰</br>
- Mark of Pusciel
>每有 1 秒未造成伤害，就获得 +2.5% 伤害，最多累计 10 秒（+2.5%/阶段）。攻击速度 -20%（-20%/阶段）
><br>可防止符文诅咒：空洞</br>
- Wrathful Binding
>造成伤害时回复 2 点生命（+2 点/阶段）。伤害 +5%（+5%/阶段）。攻击速度 +5%（+5%/阶段）。施加所有状态效果的几率 +10%（+10%/阶段）。受到伤害会获得短暂的DECAYED（衰朽）状态效果（每个阶段持续时间延长）。未造成伤害时，每 2 秒损失 5 点生命（-5 点/阶段）。
><br>可防止符文诅咒：空洞</br>

### 符文诅咒
- 脆弱/Fragility
>每层物理防御 -15%
- 阴燃/Smolder
>每层火焰防御 -15%
- 热病/Fever
>每层冰霜防御 -15%
- 导体/Conductor
>每层电击防御 -15%
- 亵渎/Profane
>每层光耀防御 -15%
- 神圣/Divine
>每层暗影防御 -15%
- 腐坏/Rot
>每层毒素防御 -15%
- 震颤/Tremor
>每层弹体散布 +4%	
- 汲取/Drain
>每层最大生命 -15	
- 脱落/Shedding
>每层总防御 -11.5%	
- 贫血/Anemia
>每层生命回复 -150%	
- 缺氧/Hypoxia
>每层受到治疗 -20%	
- 轻盈/Light
>每层受到的击退 +15%
- 哮喘/Asthma
>每层辅助技能冷却 +20%	
- 紫罗兰/Violet
>针对你的攻击有小概率变成紫色攻击（无视防御）。每层几率 +15%
- 空洞/Hollow
>你的攻击有概率造成零伤害（持续伤害同样适用）。每层几率 +15%
- 推进/Propellant
>每层弹体速度 -35%
- 摩擦/Friction
>每层弹体射程 -X 米
- 萎缩/Atrophy
>每层攻击速度 -20%
- 怠惰/Sloth
>每层移动速度 -8%、跳跃高度 -10%

## Artifacts/神器
### 说明
>Artifact（神器）是 Ecliptica 中关键的推进形式。每层在挑战 boss 前，你都需要先完成它们提供的额外目标。
><br>当前持有的 Artifact（神器）实际上决定了你接下来会进入哪张 Map。</br>
>被献祭的 Artifact（神器）还会决定你在 Eye of the Eclipse（蚀之眼）会面对哪个 Boss。
><br>把它们带到维度传送器会给全队带来属性奖励，算是对这番辛苦的回报。</br>
>如果 Artifact（神器）是集合前往维度传送器之前的最后一个目标，所有人都会获得 Haste（加速）状态，直到成功献祭一个 Artifact。
### 神器列表
- Encrypted Archive
>辅助技能冷却 -5%；移动速度 +5%
- Goblet of the Sun
>LUMINOUS（光耀）伤害 +8%；SHADOW（暗影）防御 +8%
- HC Armor Plating
>PHYSICAL（物理）防御 +7%
- Heart of Cinders
>ELEMENTAL（元素）防御 +6%
- Essence of Malice
>SHADOW（暗影）伤害 +6%；LUMINOUS（光耀）防御 +6%
- Wheel of Reincarnation
>受到治疗 +3%；最大 HP +5
- Sealed Megium
>伤害 +3%
- SparkGate Fragment
>攻击速度 +8%。弹体速度 +20%
### 神器与最终BOSS
- 当献祭的最多的神器是**HC Armor Plating**时，终局BOSS为**Jim C. Bringer**
- 当献祭的最多的神器是**Essence of Malice（主要）、Encrypted Archive、Sealed Megium、SparkGate Fragment**时，终局BOSS为**Gilgamesh**

## Maps/地图
>除功能性地图（Beginning Lobby、The End of Time）与终局地图（Altar of Destruction、Ground Zero、Bringer's Desert、Bringer Mothership）等不会生成神器的地图及Hall of Beginnings外，所有地图的神器均是随机生成，有可能仅生成一个神器，也有可能生成所有神器
- Beginning Lobby
>进入游戏、小队团灭、游戏结束都会来到这个地图，并非战斗场地
- Hall of Beginnings
>开始游戏的第一局固定为本地图，且一定会生成所有神器
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
>当终局BOSS为Gilgamesh时会进入此地图
- Ground Zero
>当Gilgamesh进入三阶段时会进入此地图
- Bringer's Desert
>当终局BOSS为Jim C. Bringer时会进入此地图
- Bringer Mothership
>当Jim C. Bringer进入三阶段时会进入此地图
- The End of Time
>当玩家击败终局BOSS后会进入此地图，可以查看一些本局战斗相关的信息，玩家需在黑洞处集合，重置一切，回到Beginning Lobby