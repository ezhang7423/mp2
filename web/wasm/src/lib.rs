mod utils;
use core::game::GameState;
use wasm_bindgen::prelude::*;



#[wasm_bindgen]
pub fn get_gamestate() -> JsValue {
    utils::set_panic_hook();

    let example = GameState::new(11, None);

    JsValue::from_serde(&example).unwrap()
}

#[wasm_bindgen]
pub fn send_gamestate(val: &JsValue) {
    let val: GameState = val.into_serde().unwrap();
    panic!("this is the end")
}
