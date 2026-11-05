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
10. [Bosses](#bosses)


## 一局的流程
1. 在 Beginning Lobby（起始大厅）选择职业，并在 Workshop Anvil（工坊铁砧）装备符文。
2. 进入地图（由上一层携带的神器决定），逐层清理敌人与BOSS。
3. 本层结束时献祭神器、挑战 Boss；击败后进入下一层。
4. 每层之间进入 The In-Between（夹层空间），用代币在三位商人处购买升级。
5. 阶段推进：每经过一次商店，相位轮盘会前进，难度与敌人构成随之变化。
6. 最终在 Eye of the Eclipse 面对终局 Boss。

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
1. 部分 Boss 只在相位值达到阈值后才会出现。
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
- [Gunmancer/枪术师](#gunmancer枪术师枪炮师光物火暗电枪)
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
>对已经处于BLEEDING（流血）状态的敌人再次施加流血时，会把已累计的全部层数转化为Hemorrhaged（出血）状态效果。
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
10% 概率施加 Frozen（冰冻）状态效果。
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
67是一个非常有趣的职业，它的技能机制和玩法都很独特。通过选择不同的元素手技能，玩家可以根据自己的喜好和战术需求来调整输出方式。个人比较推荐的是电之手和任意一种元素手的组合，然后根据电之手的左右手加成来选择左道或右道升级。推荐新手玩家选择。
#### 升级选择
详见[Twinmage.png](./Twinmage.png)

### Gunmancer/枪术师/枪炮师、（光/物/火/暗/电）枪
#### 职业介绍
只要有足够的赛博强化，再加上一门脑机接口 Blast Cannon，如今谁都能成为 Sorcerer。
#### Skills/技能
>Gunmancer 的Primary skill和Secondary skill都有选项，你可以选择不同的技能来改变效果，但每种技能最多只能选择一次。
##### primary skill: VA-11 Blast Cannon/主技能：VA-11 爆能炮
每 2 秒发射一次远距离命中扫描攻击，造成 50 点电击伤害。
此外，在攻击命中的位置产生一次小爆炸，造成该投射物 50% 的伤害。
##### Primary skill: Kinetic Flechette/主技能：动能飞镖
发射一枚远距离投射物，造成 50 点物理伤害。投射物可以穿透一名敌人，然后转向最近的敌人。 15% 概率施加BLEEDING（流血）状态效果。
##### Secondary skill: Firebomb/副技能：火焰炸弹
每 X 秒发射一枚受重力影响很强的爆炸投射物，造成 50 点火焰伤害。
该攻击命中后会在较大范围内爆炸，造成投射物 100% 的伤害
##### Secondary skill: Photon Condenser/副技能：光子冷凝器
每 0.25 秒发射一枚高速子弹，造成 10 点光耀伤害。
5% 概率施加 WEAKENED（虚弱）状态效果。
##### Secondary skill: Antimatter Accelerator/副技能：反物质加速器
每 X 秒发射一次由 5 枚投射物组成的散射弹幕，每枚造成 8 点暗影伤害；按住可收窄散布。
5% 概率施加 BREACHED（破防）状态效果。
##### Utility skill: Airblast/辅助技能：气爆冲击
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
- Gunmancer: Proficiency (Antimatter Accelerator)/枪术师：熟练（反物质加速器）
>Antimatter Accelerator 投射物数量 +1，每层 +1；暗影伤害 +5%。
- Gunmancer: Specialization/枪术师：专精
>攻击速度 +7%。辅助技能冷却 -7%
- Gunmancer: Sidestep/枪术师：侧步
>使用 Airblast Dash 后获得 2 层 HASTE（疾驰），每层升级 +1。
- Gunmancer: Bombing Run/枪术师：轰炸突袭
>使用「气爆冲刺」时会额外投出一枚炸弹，造成火焰伤害。冷却 4 秒。
- Gunmancer: Mastery/枪术师：精通
>CHARGED 射击伤害 +25%（每层 +25%）。
- Gunmancer: Marksman (VA-11 Blast Cannon)/枪术师：神射手（VA-11 爆能炮）
>周期性抛出硬币。用 Blast Cannon 击中硬币会把爆炸导向最近敌人，并使爆炸伤害提高 500%，每层 +24%；硬币尺寸 +10%，每层 +10%。由于只乘算爆炸部分，实际总伤害约为普通射击的 1.66 倍。
- Gunmancer: Lucky Seven/枪术师：幸运七
>主技能的每第 7 发子弹伤害 +50%。主技能的每第 4 发子弹伤害 -50%。
#### 编者简评
枪术师在v0.6更新后迎来了一波小加强，尤其是物枪（Kinetic Flechette）得到了显著增强，添加了转向机制，使其在群体战斗中表现更为出色，且Gilgamesh的二阶段受击判定区域非常小，而且很多动~~（多动症之神）~~，物枪的追踪可以很好的克制。推荐新手玩家选择。
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
>释放满蓄力的Aura Fist 会在你周围引发爆炸，造成火焰伤害并有 10% 概率施加Burning（燃烧）状态效果；爆炸会击退敌人。攻击速度 -30%
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
编者体验过它的两种玩法，砸锤更适合有一定游戏经验的玩家，丢锤则更适合新手玩家。但它们的共同点是难以应对移动靶，在多动症多如狗的当前版本显得略有劣势。
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
- Shield Mage: Unbreakable/盾法师：不屈
>来自 Purple Attacks 的伤害 -5%；Evasive Maneuver 护盾激活时，来自 Purple Attacks 的伤害 -10%。
- Shield Mage: Bulldozer/盾法师：推土机
>使用 Evasive Maneuver 冲刺时，会在冲刺方向造成冰霜伤害并击退敌人。
- Shield Mage: Ice Burst/盾法师：冰霜爆发
>每格挡一次攻击，提高 Ice Burst 的充能威力。
- Shield Mage: Mastery/盾法师：精通
>提高 Evasive Maneuver 护盾尺寸 X%，每层 X%。
- Shield Mage: Drainshield/盾法师：吸盾
>在防御姿态下格挡伤害时回复 5 点生命（每层 +3 点）。生命回复 -100%（每层 -100%）。
- Shield Mage: Rally Up/盾法师：鼓舞
>使用 Evasive Maneuver 护盾会给予你和附近盟友短暂的 EMPOWERED（强化）状态效果。
- Shield Mage: Warden/盾法师：守护者
>使用 Evasive Maneuver 护盾会让自身与所有队友获得RESILIENCE（韧性）状态效果，可以格挡一次伤害。辅助技能冷却 +50%（每层 +50%）
#### 编者简评
编者没有玩过牢盾，无法给出很公正的评价，但盾对一个队伍的重要性是不言而喻的，而且上手简单，但输出能力不高。

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
书奶说实话从最高游戏推出开始就比较牢，而且很吃升级，几乎是固定的模式，没有一定游戏理解很难玩好书奶，但书奶又是这个游戏至关重要的一个职业，一个10人的队伍推荐要有2名书奶和一名[猫奶](#nekomancer死灵猫使猫奶猫灵师)，才能很好的应对最终boss之一Gilgamesh，不推荐新手玩家游玩。
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
>玩家受到的所有伤害 +75%；敌人受到的所有伤害 +25%。每层持续 0.7 秒。Shadow（暗影）伤害可以施加该debuff。
- Decayed/衰朽
>受到治疗降为 0%。每层持续时间未知。玩家无法施加。
- Frozen/冰冻
>每层到期时造成冰霜伤害，每层持续 0.6 秒。每层都有概率施加“结冰”：移动速度 -75%；玩家的辅助技能冷却速率 -90%。Frost（冰霜）伤害可以施加该debuff。
- Heavy/沉重
>跳跃高度降为 0%。每层持续时间未知。玩家无法施加。
- Paralyzed/麻痹
>每层到期时造成雷电伤害，每层持续 0.3 秒。每层都有概率施加“僵直”：移动速度 -99%，并且无法攻击。不会打断正在播放攻击动画的敌人或 Boss。Electric（电击）伤害可以施加该debuff。
- Sticky/黏着
>玩家移动速度与跳跃高度降至 25%。每层持续时间未知。玩家无法施加。
- Weakened/虚弱
>玩家造成的所有伤害 -75%；敌人造成的所有伤害 -25%。每层持续 0.8 秒。Luminous（光耀）伤害可以施加该debuff。
- Bleeding/流血
>一层到期时造成物理伤害；每层持续 0.8 秒。Physical（物理）伤害可以施加该debuff。
- Burning/燃烧
>一层到期时造成火焰伤害；每层持续 0.5 秒。Fire（火焰）伤害可以施加该debuff。
- Hemorrhaged/出血
>层数到期时造成物理伤害，伤害量为「流血」的 2 倍。层数持续 0.8 秒。
- Poisoned/中毒
>一层到期时造成毒素伤害；每层持续 0.75 秒。Poison（毒素）伤害可以施加该debuff。
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
>造成伤害时回复 2 点生命（+2 点/阶段）。伤害 +5%（+5%/阶段）。攻击速度 +5%（+5%/阶段）。施加所有状态效果的几率 +10%（+10%/阶段）。受到伤害会获得短暂的Decayed（衰朽）状态效果（每个阶段持续时间延长）。未造成伤害时，每 2 秒损失 5 点生命（-5 点/阶段）。
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

## Bosses
>英文原名/别称
### 子目录
- [Maxipuss](#maxipuss哈吉米)
- [Darkmouth](#darkmouth大嘴花)
- [Kakarot](#kakarot萝卜)
- [NaN](#nan)
- [Beelzebub](#beelzebub苍蝇王)
- [Buff Noob](#buff-noob肌肉萌新)
- [Vesra](#vesra蝗虫虫母)
- [Pride](#pride)
- [Steven](#steven胖子煎饼脸)
- [Kodama](#kodama千手)
- [The Gravetender](#the-gravetender)
- [The Black Lily](#the-black-lily防御塔)
- [Zaveah](#zaveah)
- [Middleman](#middleman)
- [Ha'Kli](#hakli牛来)
- [Amaziah](#amaziah果冻人kill-you)
- [Jacked O' Lantern](#jacked-o-lantern南瓜南瓜头)
- [M-41-D](#m-41-dmaid)
- [Corus](#corus火龙)
- [Yuki](#yuki)
- [Cone Head](#cone-head路障头)
- [Mephiel](#mephiel)
- [Golden Grouch](#golden-grouch金乞丐)
- [Pandora](#pandora)
- [Abaddon](#abaddon小jim)
- [Khepri](#khepri蚁王)
- [Onyx Pilot](#onyx-pilot)
- [Bravera](#bravera)
- [O-One](#o-one)
- [Neo Pilot](#neo-pilot猫娘)
- [Jim C. Bringer](#jim-c-bringer)
- [Gilgamesh](#gilgamesh)

### Prime
#### Maxipuss/哈吉米
##### 基础数据
- 基础生命：5300
>基础生命指的是实例内仅有1名玩家且Boss刷新在第一层时的生命值（存疑）
- 阶段数：1
>对于因血量达到阈值切换的子阶段不计，仅计入游戏日志明确区分Phase1/2/3的情况
- 弱点：Frost（冰霜）, Shadow（暗影）
- 抗性：Luminous（光耀）
##### 攻击属性
- 造成Physical（物理）伤害
- 可施加Poisoned（中毒）状态
>伤害对应的debuff不会在“可施加的状态”列出
##### 行动模式
- Maxipuss 战斗由 1 个阶段组成。
- 近距离时，Maxipuss 会使用简单的拳击攻击，也会使用开场抓取。
- 对远距离目标，Maxipuss 可能会投掷毛球或跳跃。
##### 编者简评
很简单的Boss，没什么需要注意的地方

#### Darkmouth/大嘴花
##### 基础数据
- 基础生命：4200
- 阶段数：1
- 弱点：Shadow（暗影）, Poison（毒素）
- 抗性：Luminous（光耀）
>编者吐槽：Luminous（光耀）几乎是万人嫌属性，是个怪都或多或少都有抗性，弱点为Luminous（光耀）的怪少之又少
##### 攻击属性
- 造成Physical（物理）与Poison（毒素）伤害
##### 行动模式
Darkmouth会尝试与对手保持距离，并使用 2 种攻击。第一种是毒性投射物齐射，另一种是朝目标冲锋，造成明显更高的伤害。它通常会交替使用攻击，但偶尔会改变攻击模式和时机，试图让对手措手不及。
##### 编者简评
Darkmouth相对Maxipuss要稍微难一些，在单人挑战时会带来一定的压力，但多人游戏时依旧是减速带一个

#### Kakarot/萝卜
##### 基础数据
- 基础生命：5800
- 阶段数：1
- 弱点：无
- 抗性：无
##### 攻击属性
- 造成Physical（物理）伤害
##### 行动模式
- Kakarot 战斗由 1 个阶段组成。
- Kakarot 会在强力前方砸击，以及围绕自身散布小型 AoE 之间交替。
- 对远距离目标，Kakarot 可能会投掷石块，或以较低命中率向上跳跃。
##### 编者简评
Kakarot比Darkmouth简单，但比Maxipuss稍难，在单人挑战时也会带来一点压力，但多人游戏时还是减速带一个

#### NaN
##### 基础信息
- 基础生命：5300
- 阶段数：1
- 弱点与抗性：根据当前模式决定，详见行动模式
##### 攻击属性
- 造成Fire（火焰）, Frost（冰霜）, Electric（电击）, Luminous（光耀）, Shadow（暗影）伤害
##### 行动模式
- NaN 是一台可以切换为 4 种不同模式的机器，每种模式都有各自的难度和弱点。
- 切换到火焰时，NaN 会变得易受火焰伤害，并周期性向目标射击投射物，有概率点燃目标。
- 切换到冰霜时，NaN 会变得易受冰霜伤害，并向目标发射成组投射物，有概率冻结目标。
- 切换到电击时，NaN 会变得易受电击伤害，并向天空发射闪电，随后闪电会在小范围 AoE 中落下，有概率麻痹目标。
- 切换到暗影和光耀时，NaN 可以发射一圈施加 BREACHED（破防）的暗影投射物，或一排施加 WEAKENED（虚弱）的光耀投射物。值得注意的是，在这个形态下它不会弱于暗影或光耀，因为它同时采用了这两种对立元素。
##### 编者简评
NaN相对而言比较简单，但依旧比Maxipuss困难一些，单人挑战时若不注意躲避攻击，施加的各种debuff会让人很难受，至于多人游戏，依旧减速带

#### Beelzebub/苍蝇王
##### 基础信息
- 基础生命：5200
- 阶段数：1
- 弱点：Fire（火焰）, Shadow（暗影）
- 抗性：Frost（冰霜）, Luminous（光耀）, Poison（毒素）
##### 攻击属性
- 造成Physical（物理）与Poison（毒素）伤害
- 可施加Decayed（衰朽）状态
##### 行动模式
- Beelzebub 战斗由 1 个阶段组成。
- Beelzebub 可以召唤苍蝇协助战斗。当 HP 降至 50% 时，苍蝇会自动生成。
>注意，即使Beelzebub本身被击倒，召唤出的苍蝇依旧会存在，且在全部击杀完之前，玩家无法通关本层，该规则同样适用于其他会召唤扈从的Boss，以下不再赘述
##### 编者简评
Beelzebub本身不难打，但是它召唤的苍蝇很烦人，会不停骚扰你，即使在多人游戏时，苍蝇依旧很烦人。

#### Buff Noob/肌肉萌新
##### 基础信息
- 基础生命：4800
- 阶段数：1
- 弱点：Electric（电击）, Shadow（暗影）
- 抗性：Luminous（光耀）
##### 攻击属性
- 造成Physical（物理）伤害
##### 行动模式
Buff Noob 战是首次引入紫色攻击的战斗，形式是强力拍击，这些攻击会穿透对手的防御。他专注于接近敌人，并用连续打击击倒他们。当 HP 约为 40% 时，他会消耗两件物品之一：Pizza 或 Bloxy Cola，为自己治疗，并分别获得 ENFORCED（坚壁）或 EMPOWERED（强化）。再次达到 HP 阈值时，他会再次执行该动作，消耗剩下的物品。
##### 编者简评
Buff Noob不算难对付，说实话不如Beelzebub，它的紫色攻击很好躲，就是判定时间比较长，在它的动作结束前不要进入攻击范围。

### Late Prime / Early Penumbra
#### Vesra/蝗虫、虫母
##### 基础信息
- 基础生命：4800
- 阶段数：1
- 弱点：Fire（火焰）, Shadow（暗影）
- 抗性：Frost（冰霜）, Luminous（光耀）, Poison（毒素）
##### 攻击属性
- 造成Physical（物理）伤害
##### 行动模式
- Vesra 战斗由 2 个子阶段组成：常规形态和茧形态。处于茧中时，Vesra 会免疫所有伤害。
- 在常规形态下，Vesra 会在地面招式组和空中招式组之间切换。HP 降至 50% 时，Vesra 会进入茧状态，生成一只 Peltapod Guard，之后按固定间隔生成普通 Peltapod。Peltapod Guard 被击杀后（存疑），她会离开茧并回到常规形态。
##### 编者简评
Vesra不难打，把握好距离和走位的话可以无伤过关，注意它飞行时会举起大臂抵挡部分区域的伤害

#### Pride
##### 基础信息
- 基础生命：4600
- 阶段数：1
- 弱点：Electric（电击）
- 抗性：Luminous（光耀）, Shadow（暗影）
##### 攻击属性
- 造成Physical（物理）和Luminous（光耀）伤害
##### 行动模式
- Pride 主要专注于影响自身周围区域，而不是单个目标。他的许多攻击会生成爱心投射物，这些投射物会在他执行招式时环绕自身，出其不意地命中对手。他还可以施放 2 种不同光束：一种在身前召唤，另一种来自他的伞。
- Pride 可以在任意时刻飞向空中，生成一群爱心投射物，并向地面上的对手发射更多投射物，近距离跟随他们。
##### 编者简评
Pride是玩家在前期会遇到的比较抽象的Boss，虽然它的大部分攻击威胁性不算高，但是爱心投射物和投射物带来的WEAKENED（虚弱）效果很烦人。Pride在飞行状态下时，它的伞会抵挡部分区域的伤害

### Penumbra
#### Steven/胖子、煎饼脸
##### 基础信息
- 基础生命：8600
- 阶段数：1
- 弱点：Frost（冰霜）, Shadow（暗影）
- 抗性：Fire（火焰）, Luminous（光耀）
##### 攻击属性
- 造成Physical（物理）和Fire（火焰）伤害
##### 行动模式
- Steven 战斗由 2 个子阶段组成：常规形态和燃烧形态。
- 常规形态下，Steven 会打出高伤害斩击，并布置糖浆池。站在糖浆中会叠加 Sticky（黏着）减益。
- HP 降至 50% 时，Steven 会进入燃烧状态，使所有招式附加额外火焰伤害，并有概率触发 Burning（燃烧） 减益。他的糖浆招式也会射出更多糖浆池。
##### 编者简评
Steven也是比较抽象的Boss，它丢出的糖浆池真的很烦人，尤其是二阶段，在一些场地比较小的地图，你会发现遍地都是糖浆池，只能硬吃Sticky（黏着）的减速。注意，Steven在应对远距离目标时会丢出速度较快的投射物，不要以为它只是个近战Boss

#### Kodama/千手
##### 基础信息
- 基础生命：6500
- 阶段数：1
- 弱点：Luminous（光耀）
- 抗性：Physical（物理）
##### 攻击属性
- 造成Shadow（暗影）伤害
- 可施加Decayed（衰朽）, Bleeding（流血）, Heavy（沉重）状态
##### 行动模式
Kodama 是一个固定不动的 Boss，竞技场周围有一圈暗影，会持续造成伤害。它使用大型 AoE 爆破，以及召唤荆棘进行紫色攻击。
##### 编者简评
kodama还是一个抽象Boss，虽然固定不动相当于木桩，但是它的爆破和旋转激光伤害会不断干扰你的输出。部分职业可以跳到它的背上输出以躲避爆破和激光伤害，但不一定能躲避荆棘攻击。

#### The Gravetender
##### 基础信息
- 基础生命：6500
- 阶段数：1
- 弱点：Luminous（光耀）, Frost（冰霜）
- 抗性：Fire（火焰）
##### 攻击属性
- 造成Shadow（暗影）与Physical（物理）伤害
##### 行动模式
- The Gravetender 战斗由 1 个阶段组成。
- The Gravetender 是半固定 Boss，偶尔会在玩家脚下的竞技场地底钻行以移动。它有时会射出 Gravity Well，那是一个缓慢移动的球体，会把半径内所有玩家拉入其中；Gravity Well无法被击杀，只会随着时间消失。
##### 编者简评
纯木桩一个，如果完全不动就是完美的木桩怪。Gravity Well可能会有点烦人。顺带一提，Gravity Well也是召唤物，在消失前玩家无法通关。

### Late Penumbra / Early Antumbra
#### The Black Lily/防御塔
##### 基础信息
- 基础生命：6500
- 阶段数：1
- 弱点：Fire（火焰）, Frost（冰霜）
- 抗性：Luminous（光耀）, Shadow（暗影）
##### 攻击属性
- 造成Luminous（光耀）与Shadow（暗影）伤害
- 可施加Decayed（衰朽）, Bleeding（流血）状态
##### 行动模式
The Black Lily 是一个固定 Boss，可以在任意时刻召唤最多 3 个 Black Lily Token。它开局只有 2 种攻击；HP 降至 50% 后，会获得若干额外且更具毁灭性的招式，从可施加 decayed 状态效果的水洼，到能伤害战场整整半边的大型激光都有。Black Lily 的许多攻击几乎没有提示，迫使对手同时密切注意它和它的仆从，否则很容易被打个措手不及。
##### 编者简评
粪怪一个。虽然是固定Boss，但它丢出的水洼和激光攻击迫使你不停移动来找到一个安全区域，Luminous（光耀）伤害带来的WEAKENED（虚弱）效果和它为自己施加的ENFORCED（坚壁）状态会使你的伤害如同刮痧。

#### Zaveah
##### 基础信息
- 基础生命：16000
- 阶段数：1
- 弱点：Electric（电击）, Shadow（暗影）
- 抗性：Fire（火焰）, Luminous（光耀）, Poison（毒素）
##### 攻击属性
- 造成Physical（物理）与Electric（电击）伤害
- 可施加Burning（燃烧）状态
##### 行动模式+编者简评
Zaveah会使用多种技能，从会牵引玩家的旋转碰碰车到发射投射物，从使用手中的伸缩枪到召唤一系列扈从，迫使对手注意自己的走位和扈从的攻击，有一定难度。Zaveah的血量到达一定阈值后，它的旋转技能将会升级，带来更大威胁性。
>可能召唤的扈从包括：Voltwall, Voltwalker, Volt Buster

#### Middleman
##### 基础信息
- 基础生命：7800
- 阶段数：1
- 弱点：Fire（火焰）, Electric（电击）, Shadow（暗影）
- 抗性：Luminous（光耀）, Poison（毒素）
##### 攻击属性
- 造成Physical（物理）与Electric（电击）伤害
##### 行动模式
Middleman 是第一个快节奏 Boss，会持续冲锋并用双剑斩击对手。战斗中，他会高高跃入空中，然后选择飞回地面踢击，或向对手发射穿透激光。Middleman 专精近距离战斗，大多数攻击都会让他扑向对手，从而快速拉近距离。
##### 编者简评
相对比较抽象的怪，比较多动，施加的Bleeding（流血）状态也很烦，但是不算难打，多人小队基本可以零伤亡过关。

### Antumbra
#### Ha'Kli/牛来
##### 基础信息
- 基础生命：21000
- 阶段数：1
- 弱点：Frost（冰霜）, Shadow（暗影）
- 抗性：Fire（火焰）, Luminous（光耀）
##### 攻击属性
- 造成Physical（物理）与Fire（火焰）伤害
##### 行动模式+编者简评
Ha'kil作为v0.6新增的Boss拥有一定的难度，它会丢出造成大范围伤害的火球，也可以召唤移动的火柱干扰玩家，还能为自己施加ENFORCED（坚壁）和 EMPOWERED（强化）状态，伤害颇高，注意躲避其攻击，多人小队应对起来仍会有点难度。

#### Amaziah/果冻人、kill you
##### 基础信息
- 基础生命：15000
- 阶段数：1
- 弱点：Frost（冰霜）, Shadow（暗影）
- 抗性：Fire（火焰）, Luminous（光耀）, Poison（毒素）
##### 攻击属性
- 造成Physical（物理）与Poison（毒素）伤害
##### 行动模式
Amaziah 是一个毒属性 Boss，主要使用近距离攻击，所有攻击都会额外射出毒性投射物。HP 降至 60% 时，Amaziah 的招式组会扩展，可以进行更大、更致命的跳跃，扑向空中的对手，并从脸部发射光束。
##### 编者简评
依旧粪怪。多动、高伤、DoT，要素齐全，还有50%的高额Poison（毒素）抗性，使Thaumaturge（奇迹师）积攒Life Energy的效率变低，无法及时治疗。若小队练度不高，容易被团灭。

#### Jacked O' Lantern/南瓜、南瓜头
##### 基础信息
- 基础生命：18000
- 阶段数：1
- 弱点：Fire（火焰）, Shadow（暗影）, Poison（毒素）
- 抗性：Frost（冰霜）, Luminous（光耀）, Electric（电击）
##### 攻击属性
- 造成Physical（物理）与Fire（火焰）伤害
##### 行动模式
- Jacked O’ Lantern 战斗由 2 个子阶段组成。在第 2 子阶段，他所有基础挥击都会附加额外火焰投射物，所有砸击都会留下火柱。
- Jacked O’ Lantern 会在 35% HP 时转入第 2 子阶段，并治疗自身大量总 HP。在这个子阶段，他也可能选择 Bulk Up，使自己长时间获得ENFORCED（坚壁）和 EMPOWERED（强化）状态。
##### 编者简评
Jacked O’ Lantern不算难对付，但它在第2子阶段新增的招式：随机丢出火球并在场地留下火坑比较烦人，而且它的砸击有一定的追踪性。

### Late Antumbra / Early Umbra
#### M-41-D/maid
##### 基础信息
- 基础生命：1300
- 阶段数：1
- 弱点：Electric（电击）, Shadow（暗影）
- 抗性：Fire（火焰）, Luminous（光耀）, Poison（毒素）
##### 攻击属性
- 造成Electric（电击）伤害
##### 行动模式
- M-41-D 战斗由 2 个子阶段组成：标准阶段和塔阶段。
- 仅一次，当 M-41-D 达到 40% HP 时，她会召唤 2 座 Disruption Tower。每座塔会在治疗 M-41-D 和在玩家靠近时使用大型电击 AoE 之间交替。阶段转换后，M-41-D 也会变得更强，数个招式的半径会增加。
##### 编者简评
M-41-D不难打，但很烦人，它的大范围AoE伤害不高但侮辱性极强，加上施加的Paralyzed（麻痹）效果概率引发的僵直，打起来会很难受。

### Umbra
#### Corus/火龙
##### 基础信息
- 基础生命：12000
- 阶段数：2
- 弱点：Frost（冰霜）, Shadow（暗影）
- 抗性：Fire（火焰）, Luminous（光耀）
##### 攻击属性
- 造成Fire（火焰）伤害
##### 行动模式
- Corus 的战斗由两个阶段组成。第一阶段中，他每次攻击都会在战场各处释放持续火球弹幕。他也可以高高跃起，向下投掷更大的火球，留下持续伤害对手的地面火池。
- 第一阶段死亡后，他会进入第二阶段。在该阶段，他发射的大多数火球都会额外留下覆盖战场地面的火池。此外，他的跳跃攻击会留下持续存在并随时间增长的火柱。配合火池，Corus 会让战场大部分区域难以通行，使玩家在他接近时几乎没有空间躲避连番攻击。
##### 编者简评
比较抽象的Boss，伤害高、限制场地、DoT、多动，基本可以和Amaziah相提并论，但好消息是没有Poison（毒素）抗性。即便如此，练度不够的小队仍有可能被它的第二阶段团灭

#### Yuki
##### 基础信息
- 基础生命：10000
- 阶段数：2
- P1弱点：Electric（电击）
- P2弱点：Fire（火焰）
- P1抗性：无
- P2抗性：Frost（冰霜）, Electric（电击）
##### 攻击属性
- 造成Physical（物理）与Frost（冰霜）伤害
##### 行动模式
- Yuki 战斗由 2 个阶段组成：地面阶段和飞行阶段。
- 第 1 阶段中，Yuki 会尝试拳击和抓取玩家。HP 降至 50% 时，Yuki 可以捶击地面，释放紫色冲击波。
- 第 2 阶段中，Yuki 会永久处于飞行状态。Yuki 会获得远程冰攻击。HP 降至 50% 时，Yuki 会解锁完整招式组，可以用冰墙把竞技场部分区域分隔开，也能使用毁灭性的喷雾攻击。
##### 编者简评
唯一一个（存疑）会按阶段切换弱点与抗性的非终局Boss，不算难打但很多动，尤其是二阶段。同时也要注意冰墙，不能在血量不足时试图穿过，冰墙会对试图穿过的玩家造成持续的Frost（冰霜）伤害

#### Cone Head/路障头
##### 基础信息
- 基础生命：20000
- 阶段数：2
- 弱点：Shadow（暗影）
- 抗性：Luminous（光耀）
##### 攻击属性
- 造成Physical（物理）伤害
##### 行动模式
- Cone Head 的主要招式组使用交通灯机制：绿灯时移动、红灯时停下，以躲避他的攻击。第一阶段中，他会使用三把剑之一攻击对手，偶尔传送到对手身后，或用交通灯攻击覆盖战场大部分区域。如果没有正确遵守规则，会受到毁灭性伤害。约 30% HP 时，剑会从他手中飞出，他进入近战子阶段，追逐并拳击对手直到被击败。
- 第一阶段被击败后，他会进入第二阶段，拔出剩下两把剑，并完全发挥交通灯机制。现在他的每次斩击都会是红色或绿色，分别需要通过不移动或移动来躲避。他的大型交通灯 AoE 攻击现在会打击 3 次，迫使对手记住灯光顺序，否则会承受大量伤害。
##### 编者简评
“爱猫”人士，Nekomancer（死灵猫使）的大敌。交通灯机制通常会杀死Nekomancer（死灵猫使）召唤的猫猫，尤其是二阶段，交通灯AoE通常会清空场上的猫猫。其他职业好好利用交通灯机制不会显得难打。

### Late Umbra / Early Eclipse
#### Mephiel
##### 基础信息
- 基础生命：19000
- 阶段数：2
- 弱点：Luminous（光耀）
- 抗性：Electric（电击）
##### 攻击属性
- 造成Shadow（暗影）伤害
- 可施加Bleeding（流血）状态
##### 行动模式
- Mephiel 战斗由 2 个阶段组成。第 2 阶段招式组大幅扩展，先前招式也会被强化。
- Mephiel 是一个偏弹幕风格的 Boss，会用大量危险区域覆盖竞技场。第 2 阶段中，Mephiel 会获得飞行能力，让玩家有一段时间更专注于生存，而不是伤害 Boss。
- Mephiel 拥有强力的旋转披萨切刀招式，需要玩家围绕其旋转移动。
##### 编者简评
要伤害有伤害、要机制有伤害（PS：如果旋转切刀不算机制的话）。难以对付的Boss，它的技能范围大、伤害高，很容易导致小队团灭。

#### Golden Grouch/金乞丐
##### 基础信息
- 基础生命：18500
- 阶段数：1
- 弱点：Fire（火焰）, Luminous（光耀）
- 抗性：Frost（冰霜）, Electric（电击）, Poison（毒素）
##### 攻击属性
- 造成Physical（物理）与Shadow（暗影）伤害
- 可施加Decayed（衰朽）, Frozen（冰冻）, Heavy（沉重）状态
##### 行动模式
- Golden Grouch 战斗由 2 个子阶段，也就是姿态组成：剑姿态和徒手姿态。两个子阶段拥有完全不同的招式组。每场战斗一次，当 Golden Grouch 低于 70% HP 时，他的剑会被打飞，切换到徒手姿态。剑会作为被动实体留在 Gate 旁边。徒手姿态中，Golden Grouch 可以使用一个招式召唤 6 个 Shadow Grouch 敌人。该招式最多可使用 2 次。
- Shadow Grouch 的 HP 会衰减，每秒失去其最大 HP 的 3%。每 10 秒，每个 Shadow Grouch 都会给予 Golden Grouch 短暂的 INVINCIBLE（无敌）状态效果。
- 徒手姿态下 HP 低于 40% 后，Golden Grouch 会开始跑向掉落的剑，拾起它并切回剑姿态。剑姿态下，当 Golden Grouch 低于一定HP时会拥有扩展招式组。
##### 编者简评
不太好打的Boss，徒手姿态下获得的INVINCIBLE（无敌）状态和偶尔释放的AoE地板攻击带来的一系列debuff会不加烦人，当它第二次进入剑形态后还能释放大范围紫色攻击，需要及时躲避。

### Late Umbra
#### Pandora
##### 基础信息
- 基础生命：24000
- 阶段数：1
- 弱点：Fire（火焰）, Luminous（光耀）
- 抗性：Frost（冰霜）, Electric（电击）, Shadow（暗影）
##### 攻击属性
- 造成Physical（物理）与Frost（冰霜）伤害
##### 行动模式
- Pandora 是飞行 Boss，使用大型冰 AoE 和快速冲刺攻击对手。它可以制造需要跳过的冰 shard 波，并向战场横向发射冰激光。
- HP 达到 50% 后，它会变得更具侵略性，使用规模更大、更具毁灭性的攻击，并高速掠过天空，释放更大型、可穿透防御的冰爆。
##### 编者简评
依旧是一个不太好打的Boss，大型AoE和激光以及冰暴非常难以应对，练度不够的小队可能会被团灭。

### Eclipse
#### Abaddon/小Jim
##### 基础信息
- 基础生命：32000
- 阶段数：2
- 弱点：Luminous（光耀）
- 抗性：Frost（冰霜）, Electric（电击）, Fire（火焰）, Poison（毒素）
##### 攻击属性
- 造成Physical（物理）与Shadow（暗影）伤害
- 可施加Decayed（衰朽）, Heavy（沉重）状态
##### 行动模式
- Abbadon 是巨大的 Manalyte，会召唤最多 3 个 Elder Manalyte 与它并肩作战。它会施放大型 AoE 攻击，产生火柱和火球，以及可对对手施加Decayed（衰朽）的黑暗球体。
- 第一阶段死亡后，Abbadon 会蜕皮并进入第二阶段。此时它可召唤的 Manalyte 最大数量增加到 6 个。它大多数攻击现在会穿透对手防御，并拥有更大的半径。最具毁灭性的招式是吞没战场大部分区域的冲击波。
##### 编者简评
纯粹的数值怪。与终局Boss[Jim C. Bringer](#jim-c-bringer)有的一拼，不如说，很多招式很像，而且抗性也差不多。值得重视的Boss。

#### Khepri/蚁王
##### 基础信息
- 基础生命：26000
- 阶段数：2
- 弱点：Fire（火焰）, Shadow（暗影）
- 抗性：Frost（冰霜）, Luminous（光耀）
##### 攻击属性
- 造成Physical（物理）与Frost（冰霜）伤害
##### 行动模式
- Khepri 战斗由 2 个阶段组成。第 2 阶段中，Khepri 会获得大幅提升的机动性和飞行能力。
- Khepri 可以释放披萨切刀形状的强力冰攻击，这些攻击最多可连续衔接 3 次。如果第 1 阶段中玩家距离较远，它会投掷极其精准的冰刺，并总是施加Frozen（冰冻）。
- 第 2 阶段中，如果玩家接近 Khepri，它可能会选择尖叫。紫色半径内的所有人都会被施加Frozen（冰冻），而它会立即转入飞行。飞行期间，Khepri 既能抓取玩家，也能甩出撕裂般散布的冰投射物，全部都会施加长时间Frozen（冰冻）状态。
##### 编者简评
依旧数值怪。而且很多动。很容易导致小队团灭。

#### Onyx Pilot
##### 基础信息
- 基础生命：24000
- 阶段数：1
- 弱点：Fire（火焰）, Shadow（暗影）
- 抗性：Electric（电击）, Luminous（光耀）
##### 攻击属性
- 造成Physical（物理）伤害
##### 行动模式+编者简评
- Onyx Pilot大多数攻击为砸地攻击或踢腿攻击，且砸地攻击还会生成石柱造成紫色伤害。在生命值低于一定值后，Onyx Pilot将会恢复较多血量（可恢复5次），并升级它的砸地攻击，召唤更多石柱。
- 纯粹的血牛，你看到的血条其实可能只有你实际要打的血量的一半，但是整体威胁性不大。

### Late Eclipse
#### Bravera
##### 基础信息
- 基础生命：28000
- 阶段数：2
- 弱点：Fire（火焰）, Poison（毒素）
- 抗性：Frost（冰霜）, Luminous（光耀）, Electric（电击）
##### 攻击属性
- 造成Physical（物理）与Electric（电击）伤害
##### 行动模式
- Bravera 战斗由 2 个阶段组成。第 1 阶段中，Bravera 会与 2 名 Opton Guard 一起生成。Opton Guard 会寻找大厅中 HP 最低的玩家，并持续骚扰他们。伤害 Bravera 并不要求杀死守卫，因此要攻击谁由队伍自行决定。
- 第 1 阶段中，当 Bravera 达到 50% HP 时，他会解锁 2 个新招式。现在他可以使用 Corkscrew Leap 跨越长距离，也可能用强力单次打击的 Pizza-cutter 结束突进。
- 第 2 阶段开始后，Bravera 会解锁新的招式组。这套招式比第一阶段敏捷得多，包含激烈近战连段和冲刺能力，使得没有队友支援时很难逃离 Bravera。第 2 阶段中，当 HP 达到 50% 时，Bravera 可以使用先前 Pizza-cutter 的强化版本，现在会打击两次，并且可在任意时刻使用。
##### 编者简评
依旧数值怪。伤害高、骚扰性强。很容易使小队团灭。

#### O-One
##### 基础信息
- 基础生命：16000
- 阶段数：1
- 弱点：Frost（冰霜）, Shadow（暗影）
- 抗性：Luminous（光耀）
##### 攻击属性
- 造成Physical（物理）伤害
- 可施加Paralyzed（麻痹）状态
##### 行动模式
- O-One 战斗有两个子阶段。
- 第一子阶段中，他使用一把小战斧和一把手枪。他通常会绕着对手移动并射击，偶尔冲入近身用斧头攻击。他大多重复“远距离射击”和“高速近身斩击”这一循环。
- 当 HP 达到 40% 时，他会换下武器，改用单剑，并以更高速度和新攻击在近距离攻击对手。
##### 编者简评
不算难打，除了多动也没有什么槽点，在Late Eclipse这个“群英荟萃”的阶段显得很朴素。

#### Neo Pilot/猫娘
##### 基础信息
- 基础生命：27000
- 阶段数：1
- 弱点：Fire（火焰）, Shadow（暗影）
- 抗性：Luminous（光耀）, Electric（电击）
##### 攻击属性
- 造成Physical（物理）与Electric（电击）伤害
- 可以施加Heavy（沉重）状态
##### 行动模式
- Neo Pilot 战斗由 2 个子阶段组成。如果玩家在对抗 Neo Pilot 时升空，她会跃向他们并尝试踢击两次。这些踢击有概率施加Heavy（沉重）状态效果。
- 常规状态下，Neo Pilot 会使用斩击和横移。HP 达到 70% 后，她会开始从远距离跳向玩家。
- 每场战斗一次，当 HP 达到 40% 时，Neo Pilot 会进入第 2 子阶段。她会治疗大量 HP，并让所有跳跃附带电击冲击波，玩家必须跳过以躲避。她的近战攻击也会获得显著速度提升。再次达到 40% HP 后，Neo Pilot 会解锁两个强力新招式。第一个是朝前方释放、几乎瞬间发动的 tankbuster，要求玩家保持距离。第二个是快速打击的三连 pizza-cutter。
##### 编者简评
粪怪一个。第二个子阶段的冲击波很烦人，伤害很高。很容易导致小队团灭。

### Eye of the Eclipse
#### Jim C. Bringer
##### 基础信息
- 基础生命：50000
- 阶段数：3
- 弱点：无
- P1抗性：无
>P2免疫所有伤害，详见行动模式
- P3抗性：Elemental（元素）
##### 攻击属性
- 造成Physical（物理）伤害
##### 行动模式
**Jim 的所有直接近战攻击都会造成 PURPLE（紫色）伤害！**
- 第 1 阶段：第 1 阶段中，Jim 对所有伤害形式都为中性。攻击时，他会打出强力且范围很长的拳击，并无视任何吸引仇恨能力，因为整场战斗所有阶段中他的仇恨目标完全随机。HP 达到 70% 时，Jim 会解锁更多招式，包括长距离跳跃和臭名昭著的强力激光。HP 达到 40% 时，Jim 可以施放 Cataclysm，这是一种长时间引导、接近竞技场大小的核爆。站在 Cataclysm 中心半径内会被瞬间击杀，但离开中心越远，伤害会逐渐降低。施放 Cataclysm 后他会长时间处于被动状态，因此建议在 Cataclysm 结束后利用这段时间恢复队伍生命，并复活死亡玩家。
>在 70%、50% 和 30% HP 时，Jim 会暂停并召唤一台 Jim’s Wedge，这是一种强力支援敌人，会从远距离开火。
- 第 2 阶段：第 2 阶段开始时，Jim 会进入 Flipper MK.II Abyssal，并在整个阶段中一直待在里面。Flipper 免疫所有伤害，会把任何伤害视为 Blocked。它拥有 3 个招式：以极高速度冲撞玩家，造成重度紫色伤害；部署 Jim’s Wedge；从任意距离向目标发射火箭弹幕。
>经过 2 分钟后，4 座 Signal Tower 会落在竞技场四角。玩家必须站在这些 Signal Tower 内为其充能。单独充能时，每座 Signal Tower 需要 30 秒，但这个时长会随大厅玩家数量增加。多名玩家站在同一座 Signal Tower 下会提高充能速度。全部 4 座 Signal Tower 充能完成后，轨道打击会落在 Flipper 上并将其摧毁。
- 第 3 阶段：第 3 阶段由 2 个子阶段组成。Jim 的行为类似原本的第 1 阶段，但整个招式组都被强化。他挥击更快，连段更长，并解锁极其强力的连段终结技。除物理外，Jim 现在还会获得对所有元素 0.75x 的抗性。
>HP 达到 70% 时，Jim 会解锁和之前相同的招式，但这些招式再次被强化。他的激光更宽更快，跳跃会造成更高伤害。Jim 现在也可能传送到距离较远的玩家身边，或在连段中途传送，打玩家一个措手不及。
><br>HP 达到 50% 时，第 2 子阶段开始。经过较长冷却后，一个 Product Barrel 会落入竞技场。桶会直接落在 Jim 所站一侧的正对面。Jim 会变为无敌，并开始慢跑向桶。玩家必须在 Jim 到达前摧毁桶。如果 Jim 到达桶处，他会消耗它，治疗大量 HP，并获得长时间ENFORCED（坚壁）和 EMPOWERED（强化）增益。如果他因此治疗到 50% HP 以上，在再次达到该生命阈值前，他不能再投放更多桶。且在第二子阶段，Jim 的招式组会再扩展一次，解锁经常影响整个竞技场的强力招式。</br>
##### 编者简评
完美的数值+机制怪。作为终局Boss有着充分的压迫力。较低练度的小队很难轻松攻略。

#### Gilgamesh
##### 基础信息
- 基础生命：70000
- 阶段数：3
- 弱点：Fire（火焰）, Luminous（光耀）
- 抗性：Frost（冰霜）, Shadow（暗影）, Poison（毒素）
##### 攻击属性
- 造成Physical（物理）, Electric（电击）, Shadow（暗影）伤害
- 可以施加Heavy（沉重）状态
##### 行动模式
- 第一阶段：Gilgamesh会使用它的蜘蛛腿刺入场地，造成一定范围的紫色伤害，并附带覆盖全场的缓慢冲击波，玩家需要在躲避这两个攻击后对着蜘蛛腿输出。同时，Gilgamesh还会喷吐投射物或召唤闪电干扰玩家输出。此外，它还会缓慢对整个场地进行喷吐攻击，玩家需要及时躲避。
- 第二阶段：第二阶段开始时，Gilgamesh会退到场地之外，场地内会生成一只瓢虫maurice，maurice受击判定很小，有众多攻击方式，当玩家击败maurice后，maurice会攻击Gilgamesh，随后Gilgamesh进入第三阶段。
- 第三阶段：第三阶段由两个子阶段构成。第一个子阶段，Gilgamesh会使用第一阶段的大部分技能，包含蜘蛛腿砸地、召唤闪电、喷吐投射物，同时可能将玩家持续吸引到场地中心并造成伤害。另外，Gilgamesh还会解锁新的技能，包括极大范围AoE和多次蜘蛛腿砸地，这些攻击都会生成冲击波。
>在经过一段时间后，Gilgamesh会退出场地，并在场地内持续生成小蜘蛛，玩家需要进行清理，否则小蜘蛛会干扰后续的输出。在离开场地一段时间后，Gilgamesh会回到场地并释放极大范围AoE，同时生成冲击波。
><br>当玩家清空Gilgamesh的血条后，Gilgamesh会恢复所有生命值并开始蓄力，此时进入第二个子阶段，并使携带Mortal Curse（致命诅咒）倒地的玩家可以被正常复苏。玩家需要在Gilgamesh蓄力完成之前击杀Gilgamesh，否则Gilgamesh会将小队团灭。第二个子阶段，Gilgamesh会专心蓄力，偶尔召唤雷电干扰玩家，但不会再生成冲击波。</br>
##### 编者简评
粪怪一个。作为终局Boss稍显不足，尤其是不明所以的二阶段和三阶段，加上蓄力实际上是DPS检测器，虽然Jim也有类似设计，但DPS不足就强制团灭还是略有些让人诟病。