# Personal Unreal Engine Wiki

Collection of useful information about Unreal Engine game creation. I will (hopefully) update this readme when I collect some useful or insightful information for convinient easy access later.

<a name="table-of-contents"></a>
## Table of Contents

> 1. [Gameplay Ability System](#gas)
>    &nbsp;1.1 [GAS's Replication Modes](#gas-modes)

<a name="gas"></a>
## 1. Gameplay Ability System

<a name="gas-modes"></a>
### 1.1 GAS's Replication Modes

Ability System Component's Replication Mode can be set right after its creation in the constructor like this:

```c++
  ObsidianAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode);
```



