# Personal Unreal Engine Wiki

Collection of useful information about Unreal Engine game creation. I will (hopefully) update this when I collect some useful or insightful information for convinient easy access later.

<a name="table-of-contents"></a>
## Table of Contents

> 1. [Gameplay Ability System](#gas) \
>    &nbsp;1.1 [GAS's Replication Modes](#gas-modes) \
>    &nbsp;1.2 [GAS's Gameplay Effect Duration Policies](#gas-gedurationpolicies) 

<a name="gas"></a>
## 1. Gameplay Ability System

<a name="gas-modes"></a>
### 1.1 GAS's Replication Modes

The ASC defines three replication modes for replicating Gameplay Effects, Gameplay Tags and Gameplay Cues. 
Ability System Component is typicaly constructed in the OwnerActor's contructor and explicitly marked as replicated, Replication Mode can be set right after its creation like this:

```c++
  AbilitySystemComponent = CreateDefaultSubobject<UObsidianAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
  AbilitySystemComponent->SetIsReplicated(true);
  AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::OneOfThreeReplicationModes);
```
This function takes in EGameplayEffectReplicationMode enum class which is well explain by the below tabel.

| Replication Mode | Use Case                              | Description                                                                                                               |
| -----------      | ------------------------------------- | ------------------------------------------------------------------------------------------------------------------------- |
| Minimal          | Multiplayer; AI Controlled Actors     | Gameplay Effects are **not** replicated. Gameplay Cues and Gameplay Tags are replicated to all clients                    |
| Mixed            | Multiplayer; Player Controlled Actors | Gameplay Effects are replicated to the owning client only. Gameplay Cues and Gameplay Tags are replicated to all clients. |  
| Full             | Single Player                         | Every Gameplay Effect is replicated to every client.                                                                      |

<a name="gas-gedurationpolicies"></a>
### 1.2 GAS's Gameplay Effect Duration Policies

Every Attribute has a base value and a current value (this should propably has it's own explenation).
 
In the Gameplay Ability System there are 3 Gameplay Effect Duration Policies:
- Instant - affects the base value and changes it "permanently",
- Infinite - affects the current value and can be undone when the effect is removed (must be done 'manually'),
- Has Duration (non-periodic) - affect the current value and are removed after given time, meaning the current value goes back to the original value before the gameplay effect,
- Has Duration (periodic) - 



