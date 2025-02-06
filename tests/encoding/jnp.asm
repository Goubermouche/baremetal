; expect: 7bfe7bff0f8b7affffff7b7d0f8beeffffff0f8be9ffffff0f8b62ffffff0f8b5b000000

bits 64

jnp $+0
jnp $+1
jnp $+-128
jnp $+127
jnp 0
jnp 1
jnp -128
jnp 127
