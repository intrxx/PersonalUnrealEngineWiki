# Personal Unreal Engine Wiki

Collection of useful information about Unreal Engine game creation. I will (hopefully) update this when I collect some useful or insightful information for convinient easy access later.

<a name="table-of-contents"></a>
## Table of Contents

> 1. [Gameplay Ability System](#gas) \
>    &nbsp;1.1 [Ability System Component](#asc) \
>    &nbsp;&nbsp;1.1.1 [GAS's Replication Modes](#gas-modes) \
>    &nbsp;1.2 [Gameplay Effects](#ge) \
>    &nbsp;&nbsp;1.2.1 [Gameplay Effect Duration Policies](#gas-gedurationpolicies)  \
>    &nbsp;&nbsp;1.2.2 [Gameplay Effect's Params](#ge-params) \
>    &nbsp;&nbsp;1.2.3 [Effect Stacking](#ge-stacking) \
>    &nbsp;&nbsp;1.2.4 [Modifier Order of Operations](#ge-orderofop) 

<a name="gas"></a>
## 1. Gameplay Ability System

<a name="asc"></a>
### 1.1 Ability System Component

<a name="gas-modes"></a>
#### 1.1.1 GAS's Replication Modes

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

<a name="ge"></a>
### 1.2 Gameplay Effects

<a name="gas-gedurationpolicies"></a>
#### 1.2.1 Gameplay Effect Duration Policies

Every Attribute has a base value and a current value (this should propably has it's own explenation).
 
In the Gameplay Ability System there are 3 Gameplay Effect Duration Policies:
- **Instant** - affects the base value and changes it "permanently",
- **Infinite** - affects the current value and can be undone when the effect is removed (must be done 'manually'),
- **Has Duration** - affect the current value and are removed after given time, meaning the current value goes back to the original value before the gameplay effect,
- **Has Duration/Infinite (Periodic)** - affect the base value like instant effect - HasDuration/Infinite duration policy becomes Periodic after setting it's "Period" to be a non-zero value. Pretty much same thing here if we change the "Has Duration" into periodic it will remove itself after a given time (Duration Magnitude) and if we changes the "Infinite" one to periodic we will need to remove it 'manually'.

<a name="ge-params"></a>
#### 1.2.2 Gameplay Effect's Params

Execute Periodic Effect on Application - we can check this checkbox to have the gameplay effect "start" righ away after applying it to the ASC. A thing to note here, if we decide to apply it on application it will execute one aditional time leading to some missunderstandings and errors.

<a name="ge-stacking"></a>
#### 1.2.3 Effect Stacking

The Gameplay Effect has a stacking secion where we can choose the stacking type of a given gameplay effect. If a stacking type is set to **None** all gameplay effects of this type when applied are treated as individual gameplay effects.

**Aggregate by Source** - means that this stack limit count is enforced per source. If we have one source that applies a gameplay effect (with stack limit count set as 2) - if it applies it to the target the stack count is aggregated by the source if it applies another one the second one is aggregated and we reach the limit. Now if we have another source (source_v2) with the same gameplay effect then source_v2 can apply additional 2 stacks until it reaches it's own limit.

**Aggregate by Target** - means that this stack limit count is enforced per target. If some source applies the effect (with a stack limit count set to 1) it gets added to the stack count of the target so if any other source tries to apply the same effect it will fail as the stack limit count is reached.

Sources and Targets are simply Ability System Components applying or reciving the gameplay effects.

**Stack Limit Count** - Max amount of gameplay effects that can be applied.

**Stack Duration Refreash Policy** - it's a policy for how the effect duration should be refreashed while stacking, we can choose **Refreash on successful aplication** or **Never refreash**
- **Never Refreash** - when applying 3 gameplay effects in some amount of time the duration of the first one is the final duration and after it expiries the gameplay effect ends, 
- **Refreash on successful aplication** - when applying 3 gameplay effects in some amount of time the duration gets refreashed after applying individual gameplay effects.

**Stack Period Refreash Policy** -  esencially the same as the one above bu applying to period.

**Stack expariation policy** - Policy on how to handle duration expiring on this gameplay effect:
- **Clear entire stack** - we can just clear the whole stack and end the gameplay effect,
- **Remove single stack and refreash duration** - we can just remove 1 stack and let the duration run again,
- **Refresh duration** - if set to this, the gameplay effect becomes infinite (we can manually respond to OnStackCountChange).

<a name="ge-orderofop"></a>
#### 1.2.3 Modifier Order of Operations



