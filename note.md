constraints
- width
- height
- padding
  - positionが定義される

// 今回の実装
view { 
  size { 320, 568 },
  surface { udonge }, 
  children {
    header {
      top { parent }, horizontal{ parent }, 
      surface { back_blur }, 
      children {
        button { 
          left_header_action, 
          left { parent }, vertical { parent },
          children { view { surface { left_header }, padding { parent, 16 }, size{16} } }
        },
        button { 
          right_header_action, 
          right { parent }, vertical { parent },
          children { view { surface { right_header }, padding { parent, 16 }, size{16} } }
        },
        button {
          header_logo_action,
          center { parent }
          surface { logo },
          size { logo_x, logo_y }
        }
      }
    },
    footer {
      bottom { parent }, horizontal{ parent }, 
      surface { back_blur }
    }
  }
}

// parent で completed になる
view parent_view { size{100, 100} };
view child_view { padding{parent, 16} }; // parent は placeholder, この時点ではデータメンバを持たない

bounds(parent_view);
bounds(child_view); // データメンバを持たないので assert

parent_view.push(child_view);

bounds(child_view); // placeholder が解決されているので取得可能

// child で completed になる(一旦考えない方向でいく)

(const completed_rect& rect) {
  return padding(rect, 16);
}

// function でよくね？
// surface は invocable<graphic, bounds> を満たす concept
// on_click は invocable<position> を満たす concept
// view は top-level な concept

// xy軸に size の状態が存在する
- completed-concepts
  - `confirm`: size が確定した状態
  - `controlled`: 自身の size 依存関係が解決され、size が確定した状態
- incomplete-concepts
  - `uncontrolled`: 後天的に size が確定する状態(依存先の placeholder が解決されていない)
  - `undefined`: size が確定していない

こういう関係
- completed-concepts != incomplete-concepts
  - 状態を複数持ったり、状態を持たない`view`はない
- incomplete-concepts な値を呼ばれると assert

## 以上から考える view-concepts
```(C++)
concept view = requires(ViewType view) {
  { view.frame() } -> rect<value_type>;
  { view.bounds() } -> rect<value_type>;
  { view.transform() } -> ???
};
```
viewを型化したものが
local_bounds と affine から frame() を取得する
local_bounds が bounds()

## padding の仕様から考える relation

### 前提
`view`には`frame`と`bounds`の2つの座標が存在する
- `view.frame`
  - `frame`は客観的な座標
- `view.bounds`
  - `bounds`は主観的な座標

どれよ？
1. `local_bounds`と`transform`から`frame()`、`bounds()`にアクセスできる？
  - C++的にはこっち
2. `view`の`frame`と`bounds`は`relation`が組まれている？
  - getter, setterあったらなぁ

### 並列関係
```
padding(From, To, (optional)Size)
```

- `padding` は `From.bounds` と `To.frame` を(`Size`に依存して)一致させる `relation` を構築する
  - `relation`は型で決定したい
- `padding` は `From` か `To` のいずれか一方が `completed` でなければならない(お互い`completed`、`incomplete`は許可されない)
- `padding` は `incomplete` 側を `controlled` に昇格

#### 実例 A(undefined), B(confirm)
```
padding(A, B{size{32}}, 16)
```

- `A` は `undefined`(サイズが確定していない)
- `B{size{32}}` は `confirm`

`padding(A, B{size{32}}, 16)` 後の `A` と `B`
- `A` は `controlled`
- `B` は `confirm`

後天的に型確定できないから辛い
親子関係にすると解決できそう

```
A{ children{ B{size{32}, padding(parent, 16)} } }
```

- `A` は `undefined`(サイズが確定していない)
- `B{size{32}, padding(parent, 16)}` は `completed`

この場合の `padding(To)` は？

- `padding` は children の bounds と parent の frame を complete 側と一致させる `relation` を構築する
- `padding` は children か parent のいずれか一方が completed でなければならない
- `padding` は completed でない側を controlled にする

つまり、この `relation`

- A は controlled
- B は completed

// A{size(100)} -> B{padding{parent, 16}}
// A は completed
// B は undefined
// padding は children の bounds と parent の frame を complete 側に一致させる relation を構築する
// padding は children か parent のいずれか一方が completed でなければならない
// A は completed
// B は controlled

## うい

view は2つの座標系を持つ
親との相対座標系(topなどで操作)
自身の座標系

関係性とはx軸でいうとleft, rightの2点で制御ならstrong？

// strong 関係
// strong 関係は親子お互いの状態を強い方にできる
// 複数の strong 関係は一致しなくてはならない

// x(position-completed, size-completed), y(position-completed, size-completed)
// make_view(surfacer { left_header }, size {16}, margin{parent, 16})

// children が parent の制約を確定させる例
// child前
// x(position-undefined, size-undefined), y(position-undefined, size-undefined)
// child後
// x(position-completed, size-completed), y(position-completed, size-completed)
auto lb = left_button { 
  on_click { left_header_action }, 
  children { 
    make_view(surfacer {left_header}, size {16}, margin{parent, 16}) // make_view した view に対して padding 制約をつける
  }
};

auto rb = right_button { 
  on_click { right_header_action }, 
  children { 
    padding(make_view(surfacer {right_header}, size { 16 }), 16) 
  }
};

// x(position-undefined, size-completed), y(position-undefined, size-completed)
auto logo = center_logo {
  on_click { header_logo_action },
  surface { logo },
  size { logo_x, logo_y }
};

// x(position-lazy-complete, size-undefined), y(position-completed, size-completed)
view header { 
  surface { back_blur }, 
  top {parent}, // 前置placeholder
  children { 
    lb.constraints(left(parent)), // horizontal は header を制約する
    parent (rb, horizontal),
    center (logo)
  }
};

view footer {
  bottom { parent }, horizontal{ parent }, 
  surface { back_blur },
}

view main_viewer {
  padding { parent },
  surface { udonge }
}

main = make_app( size { 320, 568 }, children { main_viewer, header, footer } );
